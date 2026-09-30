#include <bits/stdc++.h> //version comentada unicamente para mejor entendimiento a los demas integrantes del grupo y al profe :D
using namespace std;
 
struct node{
    int id;
    node* child;
    node* parent;
    node* left;
    node* right;
    long long key;
    int degree;
    bool mark;
    node(int _id,long long _key) :id(_id) ,key(_key), degree(0), mark(false), parent(nullptr), child(nullptr), left(this), right(this) {};
};
 
 
class FibonacciHeap{
    private:
    node* minNode;
    
    bool menor_id(node* a, node* b){ //si las keys son iguales, agarrar el de menor id
        if(!a){
            return false;
        }
        if(!b) {
            return true;
        }
        
        if(a->key != b->key){
            return a->key < b->key;
        }
        return a->id < b->id; //criterio de desempate del problema
    }
    
    void cut(node* padre, node* hijo){
        // si el hijo era el único descendiente de su padre
        if(hijo == hijo->right){
            padre->child = nullptr;
        } else {
            // desconectar al hijo de la lista circular de sus hermanos
            (hijo->left)->right = hijo->right;
            (hijo->right)->left = hijo->left;
            if(hijo == padre->child){
                padre->child = hijo->right; 
            }
        }
        
        padre->degree--;
        
        // reinsertar el nodo cortado a la rootlist
        hijo->right = minNode->right;
        hijo->left = minNode;
        (minNode->right)->left = hijo;
        minNode->right = hijo;
        
        hijo->parent = nullptr;
        hijo->mark = false; 
    }
    
    void cascading_cut(node* nodito2){
        node* padresito = nodito2->parent;
        
        if(padresito != NULL){
            // si el padre no había perdido ningún hijo, lo marcamos
            if(!nodito2->mark){
                nodito2->mark = true;
            }else{
                cut(padresito, nodito2);
                cascading_cut(padresito);
            }
        }
    }
    
    void linkear(node* x, node* y){
        // quitar 'y' de la lista de raíces
        (y->left)->right = y->right;
        (y->right)->left = y->left;
        
        y->parent = x;
        if(!x->child){
            x->child = y;
            y->left = y;
            y->right = y;
        }else{
            // insertar 'y' como hermano directo dentro de la lista de hijos de 'x'
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }
        
        x->degree++;
        y->mark = false;
    }
    
    void consolidar(){
        //note que log2(300000) aprox 19, usamos un arreglo lo suficientemente grande para un grado maximo holgado
        vector<node*> D(67, nullptr); //67!
        vector<node*> rootlist;
        
        node* current = minNode;
        
        if(current){
            // guardar punteros en vector para no perder referencias durante los swap-links
            do{
                rootlist.push_back(current);
                current= current->right;
            }while(current != minNode);
            
            //mergear arboles de mismo grado
            for(node* w : rootlist){
                node* x = w;
                int degreeeee = x->degree;
                
                while(D[degreeeee]){
                    node* y = D[degreeeee];
                    if(menor_id(y,x)){
                        swap(x,y); // se garantiza que 'x' sea siempre la raíz de menor prioridad-id
                    }
                    
                    linkear(x,y);
                    D[degreeeee] = nullptr;
                    degreeeee++;
                }
                
                D[degreeeee] = x;
            }
            
            //reconstruir el nuevo rootlist y a su vez encontrar el minimo
            minNode = nullptr;
            for(node* d: D){
                if(d){
                    if(!minNode){
                        d->left = d;
                        d->right = d;
                        minNode = d;
                    }else{
                        // insertar d en la nueva lista circular
                        d->left = minNode;
                        d->right = minNode->right;
                        (minNode->right)->left = d;
                        minNode->right = d;
                        if(menor_id(d,minNode)){
                            minNode = d;
                        }
                    }
                }
            }
        }
    }
    
    public:
    
    FibonacciHeap() : minNode(nullptr){};
    
    node* insert(int id, long long key){ //insertar nodo
        node* newnode = new node(id,key);
         
        //logica de insertar en lista circular 
        if(!minNode) { //caso base (ningun nodo, insertamos uno apuntandose a el mismo)
            minNode = newnode;
            newnode->left = newnode;
            newnode->right = newnode;
        }else{
            newnode->left = minNode;
            newnode->right = minNode->right;
            (minNode->right)->left = newnode;
            minNode->right = newnode;
            if(menor_id(newnode, minNode)){
                minNode = newnode;
            }
        }
        return newnode; //retorna direccion de memoria de nodo para guardar en vector "vectorsito_ids"
    }
 
    void decrease_key(node* nodito, long long key_new){
        
        nodito->key = key_new;
        node* padre_nodito = nodito->parent;
        
        //si no cumple heap-order
        if(padre_nodito && menor_id(nodito, padre_nodito)){
            cut(padre_nodito, nodito);
            cascading_cut(padre_nodito);
        }
        if(menor_id(nodito, minNode)){
            minNode = nodito;
        }
    }//*gif hurón*
    
    int extact_min(){
        node* z = minNode;
        
        if(z->child){
            vector<node*> children;
            node* childdd = z->child;
            do {
                children.push_back(childdd);
                childdd = childdd->right;
            } while (childdd != z->child);
 
            for (node* c : children) {
                // insertar cada hijo en la lista de raíces
                c->left = minNode;
                c->right = minNode->right;
                (minNode->right)->left = c;
                minNode->right = c;
                c->parent = nullptr;
            }
        }
        
        //remover 'z' de la rootlist
        (z->left)->right = z->right;
        (z->right)->left = z->left;
        
        if(z == z->right){ //si era nodo unico del heap
            minNode = nullptr; 
        }else{
            minNode = z->right;
            consolidar();
        }
        
        int min_id = z->id;
        delete z; 
        return min_id;
    }
};
 
int main() {
 
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n,q;
    if (!(cin >> n >> q)) return 0;
    
    vector<node*> vectorsito_ids(n+q+1, nullptr); //creamos vector de tamaño n+q+1 (peor caso si todas las querys fueran insert)
    FibonacciHeap fibo;
    
    for(size_t i = 1; i <= n;i++){ //meter todas las ids en un vector(empezando desde 1 porque id = 0 no existe)
        long long v;
        cin >> v;
        vectorsito_ids[i] = fibo.insert(i,v);
    }
    
    int next_id = n+1; //siguiente id a insertar (si asi fuera el caso) seria n+1
    
    while(q--){
        int query;
        cin >> query;
        
        switch(query){
            case 1: { //insertar
                long long v;
                cin >> v;
                vectorsito_ids[next_id] = fibo.insert(next_id, v);
                next_id++;
                break;
            }
            case 2: { //extraer minimo
                cout << fibo.extact_min() << "\n"; 
                break;
            }
            case 3: { //decrementar llave
                int id_cambiar;
                long long v;
                cin >> id_cambiar >> v;
                fibo.decrease_key(vectorsito_ids[id_cambiar], v);
                break;
            }
        }
    }
}