#include <iostream>
#include <iomanip>
#include<sstream>
#include<fstream>
using namespace std;
template <typename T>
struct Nodo
{
    Nodo(T v, int b = 0, Nodo<T> *l = 0, Nodo<T> *r = 0) :
        value(v),
        balance(b),

        left(l),
        right(r)
    {}

    T value;
    int balance;

    Nodo<T> *left;
    Nodo<T> *right;

    void Imprimir(int offset = 0)
    {
        if (right) right->Imprimir(5 + offset);
        cout << setw(offset) << value << "(" << balance << ")" << endl;
        if (left) left->Imprimir(5 + offset);
    }
};

template <typename T>
class AVL
{
private:
    Nodo<T> *Raiz;

public:
    AVL(T Raiz_key) :
        Raiz(new Nodo<T>(Raiz_key, 0))
    {}
    ~AVL()
    {
        Delete(Raiz);
    }

    void Imprimir()
    {
        Raiz->Imprimir();
    }

    bool Add(T item)
    {
        return Add(item, Raiz);
    }

    bool Remove(T item)
    {
        return Remove(item, Raiz);
    }

    T Max()
    {
        return Max(Raiz);
    }

    T Min()
    {
        return Min(Raiz);
    }

private:

    void Delete(Nodo<T> *&node)
    {
        if (node != NULL)
        {
            Delete(node->left);
            Delete(node->right);

            delete node;
            node = NULL;
        }
    }

    void RotateRight(Nodo<T> *&node)
    {
        Nodo<T> *x = node;
        Nodo<T> *y = node->left;

        x->left = y->right;
        y->right = x;
        node = y;

        x->balance += 1;
        if (y->balance < 0) x->balance += -y->balance;

        y->balance += 1;
        if (x->balance > 0) y->balance += x->balance;
    }

    void RotateLeft(Nodo<T> *&node)
    {
        Nodo<T> *x = node;
        Nodo<T> *y = node->right;

        x->right = y->left;
        y->left  = x;
        node = y;

        x->balance -= 1;
        if (y->balance > 0) x->balance -= y->balance;

        y->balance -= 1;
        if (x->balance < 0) y->balance -= -x->balance;
    }

    bool IncrementBalance(Nodo<T> *&node)
    {
        node->balance++;

        if (node->balance == 0)
            return false;

        if (node->balance == 1)
            return true;

        if (node->balance == 2)
        {
            if (node->right->balance == -1)
                RotateRight(node->right);

            RotateLeft(node);

            return false;
        }

        // ERROR: initially non-balanced node
        return true;
    }

    bool DecrementBalance(Nodo<T> *&node)
    {
        node->balance--;

        if (node->balance == 0)
            return false;

        if (node->balance == -1)
            return true;

        if (node->balance == -2)
        {
            if (node->left->balance == 1)
                RotateLeft(node->left);

            RotateRight(node);

            return false;
        }

        // ERROR: initially non-balanced node
        return true;
    }

    bool Add(T item, Nodo<T> *&node)
    {
        if (node == NULL)
        {
            node = new Nodo<T>(item);
            return true;
        }
        else if (item > node->value)
        {
            return Add(item, node->right) && IncrementBalance(node);
        }
        else if(item < node->value)
        {
            return Add(item, node->left) && DecrementBalance(node);
        }

        return false; // no need to add already existing node
    }

    bool Remove(T item, Nodo<T> *&node)
    {
        if (node == NULL)
        {
            return false;
        }
        else if (node->value > item)
        {
            return Remove(item, node->left) && IncrementBalance(node);
        }
        else if (node->value < item)
        {
            return Remove(item, node->right) && DecrementBalance(node);
        }
        else // if (node->value == item)
        {
            if (node->left == NULL && node->right == NULL)
            {
                Delete(node);
            }
            else if (node->left != NULL && node->right != NULL)
            {
                // NOTE: "node" is reference to pointer, that can be
                //  changed during new remove. It is necessary to
                //  create another local pointer that cannot be changed
                //  form outside, to point current node.
                Nodo<T> *current_node = node;
                T min_node_value = Min(node->right);

                bool isHeightChanged = Remove(min_node_value, node);
                current_node->value = min_node_value;

                return isHeightChanged;
            }
            else
            {
                Nodo<T> *node_to_remove = node;

                if (node->left == NULL)
                {
                    node = node_to_remove->right;
                    node_to_remove->right = NULL;
                }
                else
                {
                    node = node_to_remove->left;
                    node_to_remove->left = NULL;
                }

                Delete(node_to_remove);
            }

            return true;
        }
    }

    T Max(const Nodo<T> *const node)
    {
        return node->right == NULL ? node->value : Max(node->right);
    }

    T Min(const Nodo<T> *const node)
    {
        return node->left == NULL ? node->value : Min(node->left);
    }
};
int main()
{
    int veces; //será el número de veces que voy a agregar un nodo
    int num; //el número que tendrá el nodo
    ifstream datos("datos.txt");
    //preparo el archivo 
    datos>>veces; //leo los datos
    datos>>num;
    veces--;
    AVL<int> A(num);
    while(veces>0) //leo los datos y creo los nodos
    {
      datos>>num; //leo dato
      
      A.Add(num);//creo nodo
      veces--;
    }
    cout<<"holaaa";
    
}

