#include <iostream>
#include <stdlib.h>

using namespace std;
#define adder 10; ///for spaces to print tree in 2D

/***  First Class
****   Node Class
****
***/
class Node
{
private:
    Node *right;
    Node *left;
    int data;
    int hieght;
public:
    Node(int d)
    {   right=NULL;
        left=NULL;
        data=d;
        hieght=0;
    }//END


    int getHieght()
    {   return hieght;
    }
    void setHieght(int h)
    {   hieght=h;
    }
    int getData()
    {   return data;
    }//END

    Node* getLeft()
    {   return left;
    }//END

    Node* getRight()
    {   return right;
    }//END

    void setLeft(Node *l)
    {   left=l;
    }//END

    void setRight(Node *r)
    {   right=r;
    }
    void setData(int d)
    {   data=d;
    }



}; ///END OF NODE CLASS





class bst_CLASS
{
private:
    Node *root;

public:
    bst_CLASS()         ///CONSTRUCTER
    {   root=NULL;
    } //END


    int max(int a, int b)        ///This is Max function
    {   if(a>b)
            return a;
        else
            return b;
    }//END


    int get_Hieght(Node *temp)
    {   if(temp==NULL)
        return -1;
        else
            return temp->getHieght();
    }//END

    int getBalanceFactor(Node *temp)
    {
        int x=(get_Hieght(temp->getLeft())-get_Hieght(temp->getRight()))
        return x;
    }//END

    void remove_with_r(int d)        ///REMOVE FOR AVL
    {   root=remove_r(d,root);
    }
    //END
    Node* remove_r(int x, Node* t)
    {   Node* temp;
        if(t == NULL)
            return NULL;
        else if(x < t->getData())
            t->setLeft(remove_r(x, t->getLeft()));
        else if(x > t->getData())
            t->setRight(remove_r(x, t->getRight()));

        //2 child
        else if(t->getLeft() && t->getRight())
        {   temp = findMin(t->getRight());
            t->setData(temp->getData());
            t->setRight(remove_r(t->getData(), t->getRight()));
        }
        else
        {   temp = t;
            if(t->getLeft() == NULL)
                t = t->getRight();
            else if(t->getRight() == NULL)
                t = t->getLeft();
            delete temp;
        }
        if(t == NULL)
            return t;

        t->setHieght(max(get_Hieght(t->getLeft()), get_Hieght(t->getRight()))+1);

        // Now check for unbalanced, if
        // If left node is deleted, right case
        if(get_Hieght(t->getLeft()) - get_Hieght(t->getRight()) == 2)
        {   // we get that it is right-right case
            if(get_Hieght(t->getLeft()->getLeft()) - get_Hieght(t->getLeft()->getRight()) == 1)
                return singleLeftRotate(t);
            // right left case
            else
                return doubleLeftRotate(t);
        }
        // If right node is deleted, left case
        else if(get_Hieght(t->getRight()) - get_Hieght(t->getLeft()) == 2)
        {   // left left case
            if(get_Hieght(t->getRight()->getRight()) - get_Hieght(t->getRight()->getLeft()) == 1)
                return singleRightRotate(t);
            // left right case
            else
                return doubleRightRotate(t);
        }
        return t;
    }


    //
    //
    //
    //

    Node* doubleLeftRotate(Node* temp)
    {   temp->setRight(singleRightRotate(temp->getRight()));
        return singleLeftRotate(temp);
    }

    Node* doubleRightRotate(Node* temp)
    {   temp->setLeft(singleLeftRotate(temp->getLeft()));
        return singleRightRotate(temp);
    }

    Node* findMin(Node* t)
    {   if(t == NULL)
            return NULL;
        else if(t->getLeft() == NULL)
            return t;
        else
            return findMin(t->getLeft());
    }

    Node* findMax(Node* t)
    {   if(t == NULL)
            return NULL;
        else if(t->getRight() == NULL)
            return t;
        else
            return findMax(t->getRight());
    }

    //
    //
    //
    //

    void add_DATA_TO_BST(int d)        ///THIS WILL ADD DATA TO BST
    {   Node *temp_new=new Node(d);    ///USING WHILE LOOP
        Node *temp = root;             ///COMPLEXITY IS BIG-O(H)
        if(root==NULL)
        {   root=temp_new;
            return;
        }
        else
        {   while(1)
            {   if(d<temp->getData())
                {   if(temp->getLeft()==NULL)
                    {   temp->setLeft(temp_new);
                        return;
                    }
                    else
                        temp=temp->getLeft();
                } // check for less
                else if(d>temp->getData())
                {   if(temp->getRight()==NULL)
                    {   temp->setRight(temp_new);
                        return;
                    }
                    else
                        temp=temp->getRight();
                }//check for greater
            }//while loop end
        }//else end
    }//ENd of function


    void add_with_r(int d)
    {
            ///*****THESE TWO FUNCTIONS WILL ADD DATA TO BST
            ///*****USING RECURSION
            ///*****COMPLEXITY IS BIG-O(H)
            ///*****SOMETIMES MAY BE SMALLER DEPENDING ON STRUCTURE
            ///*****BINARY TREEE
        root=addd(root,d);
    }//End of function



    /**
    if(temp->getLeft()==NULL && d<temp->getData())
            {
            temp->setLeft(temp2);
            temp->getLeft->setHieght(max(get_Hieght(temp->getLeft), get_Height(temp->getRight)));
            return;
            }
        else if(temp->getRight()==NULL && d>temp->getData())
            {
            temp->setRight(temp2);
            temp->getRight->setHieght(max(get_Hieght(temp->getLeft), get_Height(temp->getRight)));
            return;
            }
        else if(d<temp->getData())
            addd(d,temp->getLeft(), temp2);

        else addd(d,temp->getRight(),temp2);
    */
    Node* addd(Node *temp, int d)
    {   if(temp==NULL)
        {   temp=new Node(d);
        }
        else if(d<temp->getData())
        {   temp->setLeft((addd(temp->getLeft(),d)));
            int balf=getBalanceFactor(temp);  //Check for violation
            if(balf==2 || balf==-2)
            {   if(d<temp->getLeft()->getData())
                    temp=singleRightRotate(temp);
                else
                {   temp->setLeft(singleLeftRotate(temp->getLeft()));
                    temp=singleRightRotate(temp);
                }
            }//Inner if Balance factor
        }

        else if(d>temp->getData())
        {   temp->setRight((addd(temp->getRight(),d)));
            int b=getBalanceFactor(temp);
            if(b==2 || b==-2)
            {   if(d>temp->getRight()->getData())
                    temp=singleLeftRotate(temp);
                else
                {   temp->setRight(singleRightRotate(temp->getRight()));
                    temp=singleLeftRotate(temp);
                }


            }//Balance factor if

        }

        int x=max(get_Hieght(temp->getLeft()),get_Hieght(temp->getRight()))+1 ;
        temp->setHieght(x);
        return temp;

    }//End of function



    Node* singleRightRotate(Node* temp)      //RIGHT ROTATE FUNCTION
    {   Node* temp2 ;
        temp2 = temp->getLeft();
        temp->setLeft(temp2->getRight());
        temp2->setRight(temp);
        temp->setHieght( max(get_Hieght(temp->getLeft()), get_Hieght(temp->getRight()))+1);
        temp2->setHieght(max(get_Hieght(temp2->getLeft()), temp->getHieght())+1);
        return temp2;
        /**
        Node *temp2 = temp->getLeft();
        temp->setLeft(temp->getLeft()->getRight());
        temp2->setRight(temp);
        */
    }



    Node* singleLeftRotate(Node* temp)
    {   Node* temp2;
        temp2 = temp->getRight();
        temp->setRight(temp2->getLeft());
        temp2->setLeft(temp);
        temp->setHieght( max(get_Hieght(temp->getLeft()), get_Hieght(temp->getRight()))+1);
        temp2->setHieght ( max(get_Hieght(temp->getRight()), temp->getHieght())+1 );
        return temp2;
    }//end


    void display(int n)                    ///****THIS IS DISPLAY FUNCTION U
    {   Node *temp=root;              ///****USING RECUSRIONS
        if(temp==NULL)                ///****BIG-(N)
        {   cout<<"Empty "<<endl;
            return;
        }
        else
        {   if(n==1)
                display_IN(temp);
            else if(n==2)
                display_POST(temp);
            else if(n==3)
                display_PRE(temp);
        }
    }//END of function


    void display_IN(Node *temp)
    {   /**
            cout <<temp->getData()<<endl;
            if(temp->getLeft()!=NULL)
                display_2(temp->getLeft());
            if(temp->getRight()!=NULL)
                display_2(temp->getRight());
                */
        if(temp==NULL)
            return;
        else
        {

            display_IN(temp->getLeft());
            cout<<temp->getData()<<endl;
            display_IN(temp->getRight());

        }
    }//END of Function



    void display_PRE(Node *temp)
    {   /**
            cout <<temp->getData()<<endl;
            if(temp->getLeft()!=NULL)
                display_2(temp->getLeft());
            if(temp->getRight()!=NULL)
                display_2(temp->getRight());
                */
        if(temp==NULL)
            return;
        else
        {   cout<<temp->getData()<<endl;
            display_PRE(temp->getLeft());
            display_PRE(temp->getRight());
        }
    }//END of Function






    void display_POST(Node *temp)
    {   /**
            cout <<temp->getData()<<endl;
            if(temp->getLeft()!=NULL)
                display_2(temp->getLeft());
            if(temp->getRight()!=NULL)
                display_2(temp->getRight());
                */
        if(temp==NULL)
            return;
        else
        {   display_POST(temp->getLeft());
            display_POST(temp->getRight());
            cout<<temp->getData()<<endl;

        }
    }//END of Function
    ///***This is 2D Function
    void print_final(Node *temp, int space)     ///***PRINT TREE IN 2D
    {   if (temp == NULL)
            return;
        space += adder;

        print_final(temp->getRight(), space);
        cout<<endl;
        int x=adder;
        for (int i = x; i < space; i++)
            cout<<" ";
        cout<<temp->getData()<<"\n";
        print_final(temp->getLeft(), space);
    }//End of function

    void print_in_2D()   ///This wrapper of above function
    {   Node *temp=root;
        print_final(temp, 0);
    }//End of function


    /***********       BELOW IS SEARCH FUNCTION THAT WORKS ON RECURSION
    ************      MAX TIME COMPLEXITY IS EQUAL TO HIEGHT OF TREE
    ************      SOME TIMES SMALLER THAN HIEGHT ****/

    int searchData(Node *temp,int d)
    {   if(temp==NULL)
            return -1;
        if(d<temp->getData())
            searchData(temp->getLeft(),d);

        else if(temp->getData() < d)
            searchData(temp->getRight(),d);

        else
            return 0;
    }//end of function

    int searchDATA(int d)
    {   Node *temp=root;
        if(temp==NULL)
            return -1;
        else
        {   return searchData(temp,d);
        }
    }//End of function






};///END OF bst_CLASS

int main()
{   bst_CLASS myb;
    int choice,dat,x=0,result,n;
    do
    {   //system("CLS");
        cout <<"Enter 1 To add Data "<<endl;
        cout <<"Enter 2 To Display  "<<endl;
        cout <<"Enter 3 To Display in 2D "<<endl;
        cout <<"Enter 4 To Search For data "<<endl;
        cout <<"Enter 5 To Remove Data  "<<endl;
        cin>>choice;
        switch(choice)
        {   case 1:
                cout<<"Enter data you want add "<<endl;
                cin>>dat;
                result = myb.searchDATA(dat);
                if(result==0)
                    cout <<"Cannot add because this data is always present !!!! "<<endl;
                else
                    //    myb.add_DATA_TO_BST(dat);
                    myb.add_with_r(dat);
                break;
            case 2:
                cout<<"Which Display you want "<<endl;
                cout<<"1 ->IN-Order"<<endl<<"2 ->Post-Order "<<endl<<"3 -> Pre-Order "<<endl;
                cin>>n;
                myb.display(n);
                break;
            case 3:
                myb.print_in_2D();
                break;
            case 4:
                cout<<"Enter the data you want to search for :";
                cin>>dat;
                result = myb.searchDATA(dat);
                if(result==-1)
                    cout<<"Data is not Found "<<endl;
                else
                    cout<<"Data is Present "<<endl;
                break;
            case 5:
                cout<<"Enter data you want to remove "<<endl;
                cin>>dat;
                myb.remove_with_r(dat);
                //myb.removeData(dat);
                break;
            default:
                cout<<endl<<"Invalid Choice "<<endl<<endl;
                break;
        }
        cout <<"Enter -1 to exit    :";
        cin>>x;
    }
    while(x!=-1);
    return 0;
}
