#include<bits/stdc++.h>
using namespace std;
#define ll long long int


struct node{
	ll data,h;
	node *left,*right;
    node(){
        left=right=NULL;
    }
};

struct avl{
    ll height(node *root){
        if(root==NULL)
            return 0;
        return root->h;
    }

    int getbalance(node *root){
        if(root==NULL)
            return 0;
        return height(root->left)-height(root->right);
    }
        
    node* rightrotate(node *root){
        if(root==NULL)
            return NULL;
        node *temp=root->left;
        root->left=temp->right;
        temp->right=root;
        root->h=1+max(height(root->left),height(root->right));
        temp->h=1+max(height(temp->left),height(temp->right));
        return temp;
    }

    node* leftrotate(node *root){
        if(root==NULL){
            return NULL;
        }
        node *temp=root->right;
        root->right=temp->left;
        temp->left=root;
        root->h=1+max(height(root->left),height(root->right));
        temp->h=1+max(height(temp->left),height(temp->right));
        return temp;
    }

    node* insert(node *root,ll val){
        if(root==NULL){
            root=new node;
            root->data=val;
            root->h=1;
            return root;
        }

        if(val<=root->data){
            root->left=insert(root->left,val);
        }
        else {
            root->right=insert(root->right,val);
        }

        root->h=1+max(height(root->left),height(root->right));
        ll bal=getbalance(root);

        if(bal>1 && val<root->left->data){
            return rightrotate(root);
        }
        if(bal<-1 && val>root->right->data){
            return leftrotate(root);
        }
        if(bal>1 && val>root->left->data){
            root->left=leftrotate(root->left);
            return rightrotate(root);
        }
        if(bal<-1 && val<root->right->data){
            root->right=rightrotate(root->right);
            return leftrotate(root);
        }
        return root;
    }

    int maxr(node *root){
        if(root->right==NULL)
            return root->data;
        return maxr(root->right);
    }

    node* dlete(node *root,ll val){
        if(root==NULL)
            return root;
        if(val<root->data){
            root->left=dlete(root->left,val);
        }
        else if(val>root->data){
            root->right=dlete(root->right,val);
        }
        else{
            if(root->left==NULL){
                node *temp=root->right;
                delete(root);
                root=temp;
            }
            else if(root->right==NULL){
                node *temp=root->left;
                delete(root);
                root=temp;
            }
            else{
                int temp=maxr(root->left);
                root->data=temp;
                root->left=dlete(root->left,temp);
            }
        }

        if(root==NULL)
            return root;

        root->h=1+max(height(root->left),height(root->right));
        ll bal=getbalance(root);

        if(bal>1 && val<root->left->data){
            return rightrotate(root);
        }
        if(bal<-1 && val>root->right->data){
            return leftrotate(root);
        }
        if(bal>1 && val>root->left->data){
            root->left=leftrotate(root->left);
            return rightrotate(root);
        }
        if(bal<-1 && val<root->right->data){
            root->right=rightrotate(root->right);
            return leftrotate(root);
        }
        return root;
    }

    void inorder(node *root){
        if(root==NULL)
            return;
        inorder(root->left);
        cout<<root->data<<" ";
        inorder(root->right);
    }
};


    int main(){
        ios_base::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        avl obj;
    }