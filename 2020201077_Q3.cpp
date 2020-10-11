#include<bits/stdc++.h>
using namespace std;
template<class T,class V>
class orderedmap
{
   public:
        class node{
            public:
                T key;
                V value;
                int height;
                node * left;
                node * right;
                node(T k , V v ){
                    height = 1; 
                    key = k;
                    value = v;
                    left = NULL;
                    right = NULL;
                }
        };  
         node * root = NULL;
        int n = 0;
        vector<T> arr;
        void insert(T k,V v){
            node *pq = searchUtil(root,k);
            if(pq != NULL)
            {
                pq->value = v;
                return;
            }
            root=insertUtil(root, k,v);
        } // closing of insert
        void remove(T k){
            node *pq = searchUtil(root,k);
            if(pq == NULL)
            {
                return;
            }
            root=removeUtil(root, k);
        } //closing of remove
        bool search(T k){
            node*pq =  searchUtil(root,k);
            if(pq == NULL)
             return false;
             return true;
        }// closing of search
        void size()
        {
            cout<<n<<endl;
        }// closing of size
        void clear()
        {  n = 0;
            clearUtil(root);
        } // closing of clear
        void print()
        {
            node *pq = root;
            printUtil(pq);
        }
        V& operator[] (T key)
        {
            node* temp = searchUtil(root,key);
            if(temp)
              return temp->value;
           else
           {
               string s;
               V value;
               if(typeid(s).hash_code() == typeid(V).hash_code())
               {
                   value=V{};
                   insertUtil(root,key,value);
               }
               else
               {
                   insertUtil(root,key,value);
               }
               node* t = searchUtil(root , key);
               return t->value;
               
           }
              
        } // closing of operator overload
        private:
        int height(node * head){
            if(head==NULL) return 0;
            return head->height;
        } // closing of height
        node * rightRotation(node * head){
            node * pq = head->left;
            head->left = pq->right;
            pq->right = head;
            head->height = 1+max(height(head->left), height(head->right));
            pq->height = 1+max(height(pq->left), height(pq->right));
            return pq;
        } //closing of right rotation
          node * leftRotation(node * head){
            node * pq = head->right;
            head->right = pq->left;
            pq->left = head;
            head->height = 1+max(height(head->left), height(head->right));
            pq->height = 1+max(height(pq->left), height(pq->right));
            return pq;
        } // closing of left rotation 
        node * insertUtil(node * head, T x,V v){
            if(head==NULL){
                n+=1;
                node * temp = new node(x,v);
                return temp;
            }
            
            if(x < head->key) head->left = insertUtil(head->left, x,v);
            else if(x > head->key) head->right = insertUtil(head->right, x,v);
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(x < head->left->key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal<-1){
                if(x > head->right->key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
            }//closing of insert util
             node * removeUtil(node * head, T x){
             if(head==NULL) return NULL;
             n = n-1;
             if(x < head->key){
                head->left = removeUtil(head->left, x);
             }else if(x > head->key){
                head->right = removeUtil(head->right, x);
             }else{
                node * r = head->right;
                if(head->right==NULL){
                    node * l = head->left;
                    delete(head);
                    head = l;
                }else if(head->left==NULL){
                    delete(head);
                    head = r;
                }else{
                    while(r->left!=NULL) r = r->left;
                    head->key = r->key;
                    head->right = removeUtil(head->right, r->key);
                }
            }
            if(head==NULL) return head;
            head->height = 1 + max(height(head->left), height(head->right));
            int bal = height(head->left) - height(head->right);
            if(bal>1){
                if(x > head->left->key){
                    return rightRotation(head);
                }else{
                    head->left = leftRotation(head->left);
                    return rightRotation(head);
                }
            }else if(bal < -1){
                if(x < head->right->key){
                    return leftRotation(head);
                }else{
                    head->right = rightRotation(head->right);
                    return leftRotation(head);
                }
            }
            return head;
        }// closing removeUtil
        node * searchUtil(node * head, T x){
            if(head == NULL) return NULL;
            T k = head->key;
            if(k == x) return head;
            if(k > x) return searchUtil(head->left, x);
            if(k < x) return searchUtil(head->right, x);
        }// closing of searchUtil;
        void clearUtil(node *head)
        {
            if(head == NULL)
            return;
            clearUtil(head->left);
            clearUtil(head->right);
            delete(head);
        }// closing of clearUtil
        void printUtil(node * head)
        {
            if(head == NULL)
            return;
            printUtil(head->left);
            cout<<head->key<<"->"<<head->value<<endl;
            printUtil(head->right);
        }// closing of printUtil
};// closing of class
int main()
{
   orderedmap<T,V> t;
   int n;
   cin>>n;
   while(n--)
   {
       int ch;
       cin>>ch;
       while(ch--)
       {
           if(ch == 1)
           {    T key;
                V value;
                cin>>key>>value;
               t.insert(key,value);
               t.print();
           }
           else if(ch == 2)
           {
               T key;
               cin>>key;
               t.erase(key);
               t.print();
           }
           else if(ch == 3)
           {
              T key;
              cin>>key;
              t.search(key);
           }
           else if (ch == 4)
           {

           }
           else if(ch == 5)
           {
               t.size();
               t.print();
           }
           else if(ch == 6)
           {
               t.clear();
               t.size();
           }
       }
   }
    
    return 0;

}