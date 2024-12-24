#include <iostream>
using namespace std;

//Cấu trúc cây AVL
struct Node
{
  int key;
  int height;
  Node *left;
  Node *right;
};

//Trả về chiều cao của node
int
height (Node *node)
{
  if (node == NULL)
    return 0;
  return node->height;
}

//Trả về giá trị lớn nhất giữa hai số
int
max (int a, int b)
{
  return (a > b) ? a : b;
}

//Tạo một node mới
Node *
create_node (int key)
{
  Node *node = new Node ();
  node->key = key;
  node->height = 1; //Chiều cao ban đầu = 1
  node->left = NULL;
  node->right = NULL;
  return node;
}

//Xoay phải
Node *
rotate_right (Node *y)
{
  Node *x = y->left;
  Node *T2 = x->right;

  //Thực hiện xoay
  x->right = y;
  y->left = T2;

  //Cập nhật chiều cao
  y->height = max (height (y->left), height (y->right)) + 1;
  x->height = max (height (x->left), height (x->right)) + 1;

  //Trả về node mới
  return x;
}

//Xoay trái
Node *
rotate_left (Node *x)
{
  Node *y = x->right;
  Node *T2 = y->left;

  //Thực hiện xoay
  y->left = x;
  x->right = T2;

  //Cập nhật chiều cao
  x->height = max (height (x->left), height (x->right)) + 1;
  y->height = max (height (y->left), height (y->right)) + 1;

  // Trả về node mới
  return y;
}

//Tính hệ số cân bằng của node
int
get_balance (Node *node)
{
  if (node == NULL)
    return 0;
  return height (node->left) - height (node->right);
}

//Thêm một phần tử vào cây AVL
Node *
insert (Node *node, int key)
{
  //B1: Thêm phần tử vào cây nhị phân tìm kiếm thông thường
  if (node == NULL)
    return create_node (key);

  if (key < node->key)
    node->left = insert (node->left, key);
  else if (key > node->key)
    node->right = insert (node->right, key);
  else //Không cho phép các giá trị trùng lặp
    return node;

  //B2: Cập nhật chiều cao của node hiện tại
  node->height = 1 + max (height (node->left), height (node->right));

  //B3: Tính hệ số cân bằng của node
  int balance = get_balance (node);

  //B4: Kiểm tra hệ số cân bằng và thực hiện các phép xoay nếu cần

  //Trường hợp mất cân bằng trái-trái
  if (balance > 1 && key < node->left->key)
    return rotate_right (node);

  //Trường hợp mất cân bằng phải-phải
  if (balance < -1 && key > node->right->key)
    return rotate_left (node);

  //Trường hợp mất cân bằng trái-phải
  if (balance > 1 && key > node->left->key)
    {
      node->left = rotate_left (node->left);
      return rotate_right (node);
    }

  //Trường hợp mất cân bằng phải-trái
  if (balance < -1 && key < node->right->key)
    {
      node->right = rotate_right (node->right);
      return rotate_left (node);
    }

  //Trả về node hiện tại (không cần xoay)
  return node;
}

//Duyệt cây theo thứ tự giữa (Inorder Traversal)
void
inorder (Node *root)
{
  if (root != NULL)
    {
      inorder (root->left);
      cout << root->key << " ";
      inorder (root->right);
    }
}

int
main ()
{
  Node *root = NULL;
  int arr[] = {240, 73, 101, 21, 13, 25, 11, 37, 89, 30, 15, 51};
  int n = sizeof (arr) / sizeof (arr[0]);

  for (int i = 0; i < n; i++)
    {
      root = insert (root, arr[i]);
      cout << "Cay AVL sau khi them phan tu " << arr[i] << ": ";
      inorder (root);
      cout << endl;
    }

  return 0;
}
