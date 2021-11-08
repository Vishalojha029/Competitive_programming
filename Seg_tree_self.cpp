
struct item{
    int x;

};

struct segtree{
    int size;
    vector<item> values;

    void init(int n){
        size=1;
        while(size<n)size*=2;
        values.resize(2*size);
    }
    item neutral_element={0};

    item single(int v){
        return {v};
    }

    item merge(item a,item b){
        return {a.x+b.x};
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

    void set(int i,int v,int x,int lx,int rx){
        if(rx-lx==1){
            values[x]=single(v);
            return;
        }
        int mid=(lx+rx)/2;
        if(i<mid){
            set(i,v,2*x+1,lx,mid);
        }
        else{
            set(i,v,2*x+2,mid,rx);
        }
        values[x]=merge(values[2*x+1],values[2*x+2]);
    }

    void set(int i,int v){
        set(i,v,0,0,size);
    }
    item get(int l,int r,int x,int lx,int rx){
        if(r<=lx ||l>=rx){
            return neutral_element;
        }
        if(lx>=l && rx<=r){
            return values[x];
        }
        int mid=(lx+rx)/2;
        item d1=get(l,r,2*x+1,lx,mid);
        item d2=get(l,r,2*x+2,mid,rx);
        return merge(d1,d2);
    }

    item get(int l,int r){
        return get(l,r,0,0,size);
    }



};