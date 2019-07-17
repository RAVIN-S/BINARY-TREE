#include<bits/stdc++.h>
#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#define COUNT 10
using namespace std;
struct node{
   node *left;
    node *right;
    int info;
};
int arr[40],i=0;
node *stack1[30];
int top=-1;
void push(node *n){
    top++;
    stack1[top]=n;
}
node* pop(){
    if(top==-1)
        return NULL;
    return stack1[top--];
}

void postorder(node *t)
{
  if(t!=NULL)
  {
    postorder(t->left);
    postorder(t->right);
    arr[++i]=t->info;
  }
}
int inorder(node *Root){
    i=0;
    node *ptr=Root;
    point1:
        if(ptr==NULL){
            return 0;
        }
    while(ptr!=NULL){
        push(ptr);
        ptr=ptr->left;
    }
    ptr=pop();
    point2:
        if(ptr==NULL)
            return 0;
    arr[++i]=ptr->info;
    if(ptr->right!=NULL){
        ptr=ptr->right;
        goto point1;
    }
    else{
        ptr=pop();
        goto point2;
    }
    return 0;
}
void search(node *Root,int item,node **cur,node **parptr){
    node *ptr=Root;
    while(ptr!=NULL){
        if(ptr->info==item){
            *cur=ptr;
            return;
        }
        else if(ptr->info>item){
                *parptr=ptr;
            ptr=ptr->left;
        }
        else{
            *parptr=ptr;
            ptr=ptr->right;
        }
    }
}
 void delete1(node **Root,int item)
{
    node *ptr=NULL,*parptr=NULL;
    int cas;
    node *z=*Root;
    if(z->info==item&&(z->left==NULL&&z->right==NULL)){
        node *x=z;
        *Root=NULL;
        free(x);
        return;
    }
   // point2:
    search(*Root,item,&ptr,&parptr);
    if(ptr==NULL){
        cout<<endl<<"Item not found"<<endl;
        return;
    }
    else{
            point1:
            if(ptr->left==NULL&&ptr->right==NULL)
            cas=1;
    else if((ptr->left==NULL&&ptr->right!=NULL)||(ptr->left!=NULL&&ptr->right==NULL))
        cas=2;
    else
        cas=3;
    }
    switch(cas){
    case 1:if(parptr!=NULL){
        if(parptr->right==ptr){
           parptr->right=NULL;
           free(ptr);
        }
        else{
           parptr->left=NULL;
           free(ptr);
        }
    }
    else{
        *Root==NULL;
        free(ptr);
    }
    cout<<endl<<"Item deleted"<<endl;
    return;
    case 2:
        if(ptr->left!=NULL){
                parptr=ptr;
        ptr=ptr->left;
            int temp=parptr->info;
            parptr->info=ptr->info;
            ptr->info=temp;
        }
        else{
            parptr=ptr;
            ptr=ptr->right;
            int temp=parptr->info;
            parptr->info=ptr->info;
            ptr->info=temp;
        }
        goto point1;
        return;
    case 3:
        inorder(*Root);
        int a;
        for(a=1;a<=i;a++){
            if(arr[a]==item)
            break;
        }
        node *ptr1=NULL,*parptr1=NULL;
        search(*Root,arr[a+1],&ptr1,&parptr1);
        int temp=ptr->info;
        ptr->info=ptr1->info;
        ptr1->info=temp;
        ptr=ptr1;
        parptr=parptr1;
        goto point1;
        return;
    }
}
void insert1(node **Root,int item){
   node *neww=new node;
    neww->info=item;
    neww->left=NULL;
    neww->right=NULL;
    if(*Root==NULL){
        *Root=neww;
    }
    else{
    node *ptr,*save;
    ptr=*Root;
    save=ptr;
    while(ptr!=NULL){
        if(ptr->info>item){
            save=ptr;
            ptr=ptr->left;
        }
        else
        {
            save=ptr;
            ptr=ptr->right;
             }
    }
    if(save->info<item){
        save->right=neww;
    }
    else{
        save->left=neww;
    }
    }
    cout<<"Node Added";
}
void display(){
            int j;
            printf("\n");
        for(j=1;j<=i;j++){
            printf("%d ",arr[j]);
        }
}
int main()
{
int ch=0,ele;
node *Root=NULL;
while(ch!=4){
cout<<"\n1.Insert\n2.Delete\n3.search\n4.Display \n";
cin>>ch;
if(ch==1){
    cout<<"\nEnter the element\t";
    cin>>ele;
    insert1(&Root,ele);
}
else if(ch==2){
    cout<<"Enter the item\t";
    cin>>ele;
    delete1(&Root,ele);
}
else if(ch==3){
    cout<<"\nEnter the element\t";
    cin>>ele;
    node *ptr=NULL,*parptr=NULL;
    search(Root,ele,&ptr,&parptr);
    if(ptr==NULL){
        cout<<"\nElement not found in the tree";
    }
    else if(parptr==NULL){
        cout<<"\nItem found and it is Root of the tree";
    }
    else{
        cout<<"\nItem found and it's parent is "<<parptr->info;
    }
}
else{
        if(Root==NULL){
            printf("\nTree is empty\n");
            return 0;
        }
        inorder(Root);
        printf("\nInorder Traversal\n");
        display();
        i=0;
        postorder(Root);
        printf("\nInorder Traversal\n");
        display();
}
}
    return 0;
}
