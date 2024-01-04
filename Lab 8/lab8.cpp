#include<bits/stdc++.h>
using namespace std;
struct et{
    char val;
    et *left,*right;
};
bool isOperator(char c){
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^'){
        return true;
    }
    return false;
}
void inOrder(et *t){
    if(t){
        inOrder(t->left);
        cout<<t->val<<' ';
        inOrder(t->right);
    }
}
et* newNode(char v){
    et *temp = new et;
    temp->left = NULL;
    temp->right = NULL;
    temp->val = v;
    return temp;
}

et* constructTree(string pf){
    stack<et *> st;
    et *t,*t1,*t2;
    for(char c:pf){
        if(!isOperator(c)){
            t = newNode(c);
            st.push(t);
        }
        else{
            t = newNode(c);
            t1 = st.top();
            st.pop();
            t2 = st.top();
            st.pop();
            t->right = t1;
            t->left = t2;
            st.push(t);

        }
    }
    t = st.top();
    st.pop();
    return t;


}
int main(){
    cout <<"Enter expression in postfix form: ";
    string s;
    cin >> s;
    et *r = constructTree(s);
    cout<<"The Expression Tree is: ";
    inOrder(r);
    return 0;
}