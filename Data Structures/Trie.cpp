struct node{
    vector<ll>val;
    vector<node*>pt;
    node(){}
    node(ll c){
        val.resize(c,0);
        pt.resize(c,NULL);
    }
};
struct trie{
    ll chr;
    trie(ll c){
        chr=c;
    }
    void add(node *root, string &s){
        node *cur=root;
        for(auto x:s){
            if(cur->val[x-'a']==0){
                cur->val[x-'a']=1;
                cur->pt[x-'a']=new node(chr);
            }
            cur=cur->pt[x-'a'];
        }
    }
    ll find(node *root, string &s, ll x){
        if(s[x]=='\0')
            return 1;
        if(root->val[s[x]-'a']==0){
            return 0;
        }
        else{
            return find(root->pt[s[x]-'a'],s,x+1);
        }
    }
};  
int main(){
    trie obj(26);
    node *root=new node(26);
    ll q;
    cin>>q;
    while(q--){
        ll a;
        cin>>a;
        if(a==1){
            string s;
            cin>>s;
            cout << obj.find(root,s,0) << "\n";
        }
        else{
            string s;
            cin>>s;
            obj.add(root,s);
        }
    }
}