
struct item{
    int x,y;

};

struct segtree{
    int size;
    vector<item> values;
    vector<int>lazy;

    void init(int n){
        size=1;
        while(size<n)size*=2;
        values.resize(2*size);
        lazy.assign(2*size,NO_OP);
    }
    
    long long NO_OP=0;
    item neutral_element={0,0};

    item single(int v){
        if(v==1){
            return {1,0};
        }
        else{
            return {0,1};
        }
    }

    item merge(item a,item b){
        return {a.x+b.x,a.y+b.y};
    }
    
    int lazy_merge(int x,int y){
        // if(y==NO_OP){
        //     return x;
        // }
        // if(x==NO_OP){
        //     return y;
        // }
        return (x^y);


    }
    void apply_lazy_merge(int &x,int y){
        x=lazy_merge(x,y);
    }
    void lazy_propagate(int x,int lx,int rx){
        if(rx-lx==1){
            return;
        }
        apply_lazy_merge(lazy[2*x+1],lazy[x]);
        concate_lazy(values[2*x+1],lazy[x]);
        apply_lazy_merge(lazy[2*x+2],lazy[x]);
        concate_lazy(values[2*x+2],lazy[x]);
        lazy[x]=NO_OP;
    }
    concate_lazy(item &x,int v){
        if(v>=1){
            swap(x.x,x.y);
        }
        
    }

    void build(vector<int> &a,int x,int lx,int rx){
        if(rx-lx==1){
            if(lx<(int)a.size()){
                values[x]=single(a[lx]);
            }
            return;
        }
        int mid=(rx+lx)/2;
        build(a,2*x+1,lx,mid);
        build(a,2*x+2,mid,rx);
        values[x]=merge(values[2*x+1],values[2*x+2]);

    }

    void build(vector<int> &a){
        build(a,0,0,size);
    }

    void set(int l,int r,int v,int x,int lx,int rx){
        lazy_propagate(x,lx,rx);
        if(r<=lx ||l>=rx){
            return;
        }
        if(lx>=l && rx<=r){
            apply_lazy_merge(lazy[x],v);
            concate_lazy(values[x],v);
            return;
        }

        int mid=(lx+rx)/2;
        set(l,r,v,2*x+1,lx,mid);
        set(l,r,v,2*x+2,mid,rx);
        values[x]=merge(values[2*x+1],values[2*x+2]);
        
    }

    void set(int l,int r,int v){
        set(l,r,v,0,0,size);
    }
    item get(int l,int r,int x,int lx,int rx){
        lazy_propagate(x,lx,rx);
        if(r<=lx ||l>=rx){
            return neutral_element;
        }
        if(lx>=l && rx<=r){
            return values[x];
        }
        int mid=(lx+rx)/2;
        item d1=get(l,r,2*x+1,lx,mid);
        item d2=get(l,r,2*x+2,mid,rx);
        item d=merge(d1,d2);
        return d;
    }

    item get(int l,int r){
        return get(l,r,0,0,size);
    }


};
