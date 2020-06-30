#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <vector>
#include <list>
#include <random>


using namespace std;


///////////////////////////////////////
/////////////// USER //////////////////
///////////////////////////////////////

typedef struct {
    string univ;
    long double id;
    string name;
    unsigned int tweets;
    unsigned int friends;
    unsigned int followers;
    string date;
}USER;



///////////////////////////////////////
///////// Binary Search Tree //////////
///////////////////////////////////////

class Node {
    public:
        Node* left = NULL;
        Node* right = NULL;
        USER user;
};


class BST {

    private:

        Node* _root = NULL;
        int _size = 0;

    public:

        int repeated = 0;
        void add_by_id(long double, USER);
        void add_by_name(string, USER);
        USER* search_by_id(long double);
        USER* search_by_name(string);
        void print_by_id(long double);
        void print_by_name(string);
        void rec_node_clean(Node*);
        void clean(void);

};


// add id/user
void BST::add_by_id(long double id, USER x) {

    Node* node = NULL;
    node = new Node;
    node->user = x;

    if (_size == 0){
        _root = node;
        _size++;
    } else {

        Node* temp_root = _root;

        while(1){

            if (id < temp_root->user.id) {

                if (temp_root->left == NULL) {
                    temp_root->left = node;
                    _size++;
                    break;
                } else {
                    temp_root = temp_root->left;
                }

            } else if (id > temp_root->user.id) {

                if (temp_root->right == NULL) {
                    temp_root->right = node;
                    _size++;
                    break;
                } else {
                    temp_root = temp_root->right;
                }

            } else if (id == temp_root->user.id) {
                //repetido
                repeated++;
                delete node;
                break;
            }

        }

    }

}


// add name/user
void BST::add_by_name(string name, USER x) {

    Node* node = NULL;
    node = new Node;
    node->user = x;

    if (_size == 0){
        _root = node;
        _size++;
    } else {

        Node* temp_root = _root;

        while(1){

            if (name < temp_root->user.name) {

                if (temp_root->left == NULL) {
                    temp_root->left = node;
                    _size++;
                    break;
                } else {
                    temp_root = temp_root->left;
                }

            } else if (name > temp_root->user.name) {

                if (temp_root->right == NULL) {
                    temp_root->right = node;
                    _size++;
                    break;
                } else {
                    temp_root = temp_root->right;
                }

            } else if (name == temp_root->user.name) {
                //repetido
                repeated++;
                delete node;
                break;
            }

        }

    }

}


USER* BST::search_by_id(long double id) {

    USER* user = NULL;
    Node* temp_root = NULL;
    temp_root = _root;

    while(temp_root != NULL) {
        //cout << id << "  " << temp_root->user.id << endl;
        if (id < temp_root->user.id) {
            temp_root = temp_root->left;
        } else if (id > temp_root->user.id) {
            temp_root = temp_root->right;
        } else if (temp_root->user.id == id) {
            user = &temp_root->user;
            break;
        }
    }
    return user;
}


USER* BST::search_by_name(string name) {

    USER* user = NULL;
    Node* temp_root = NULL;
    temp_root = _root;

    while(temp_root != NULL) {
        //cout << name << "  " << temp_root->user.name << endl;
        if (temp_root->user.name < name) {
            temp_root = temp_root->right;
        } else if (temp_root->user.name > name) {
            temp_root = temp_root->left;
        } else if (temp_root->user.name == name) {
            user = &temp_root->user;
            break;
        }
    }
    return user;
}


void BST::print_by_id(long double id) {
    USER* user = NULL;
    user = this->search_by_id(id);
    if (user != NULL) {
        cout << user->univ << " " << user->id << " " ;
        cout << user->name << " " << user->tweets << " " ;
        cout << user->friends << " " << user->followers << " " ;
        cout << user->date << endl;
    } else {
        cout << "NONE" << endl;
    }
}


void BST::print_by_name(string name) {
    USER* user = NULL;
    user = this->search_by_name(name);
    if (user != NULL) {
        cout << user->univ << " " << user->id << " " ;
        cout << user->name << " " << user->tweets << " " ;
        cout << user->friends << " " << user->followers << " " ;
        cout << user->date << endl;
    } else {
        cout << "NONE" << endl;
    }
}


void BST::rec_node_clean(Node* node) {

    if (node != NULL) {
        if (node->left != NULL)
            rec_node_clean(node->left);
        if (node->right != NULL)
            rec_node_clean(node->right);
        delete node;
    }
}

void BST::clean(void) { this->rec_node_clean(_root); }



///////////////////////////////////////
//////////// OPENED HASH //////////////
///////////////////////////////////////

class OPENED_HASH {

    private:

        vector<list<USER>> _users;
        int _table_size = 22447;
        int _total_elements = 0;
        float _load;

    public:

        int repeated = 0;
        OPENED_HASH(void);
        unsigned int hash_function_id(long double);
        unsigned int hash_function_name(string);
        void add_by_id(long double, USER);
        void add_by_name(string, USER);
        USER* search_by_id(long double);
        USER* search_by_name(string);
        void print_by_id(long double);
        void print_by_name(string);
        void print_table_usage(void);
        void print_load(void);

};


OPENED_HASH::OPENED_HASH(void){

    for(int i=0; i<_table_size; i++) {
        _users.push_back(list<USER>());
    }
}


unsigned int OPENED_HASH::hash_function_id(long double id) {

    unsigned int key = 0;
    key = ((unsigned int)id)%_table_size;

    return(key);
}


unsigned int OPENED_HASH::hash_function_name(string name) {
    unsigned int key = 0;
    for (int i=0; i<name.size(); i++)
        key += (unsigned int)name[i]*i*i*i;

    key = key%_table_size;

    return(key);
}


// add id/user
void OPENED_HASH::add_by_id(long double id, USER x) {

    if (this->search_by_id(id) != NULL) {
        repeated++;
    } else {
        unsigned int key = this->hash_function_id(id);
        _users[key].insert(_users[key].begin(), x);
        _total_elements++;
        _load = 1.0*_total_elements/_table_size;
    }
}


// add name/user
void OPENED_HASH::add_by_name(string name, USER x) {
    if (this->search_by_name(name) != NULL) {
        repeated++;
    } else {
        unsigned int key = this->hash_function_name(name);
        _users[key].insert(_users[key].begin(), x);
        _total_elements++;
        _load = 1.0*_total_elements/_table_size;
    }
}


USER* OPENED_HASH::search_by_id(long double id) {

    USER* user = NULL;
    list<USER>::iterator it;
    unsigned int key = this->hash_function_id(id);

    for(it=_users[key].begin(); it!=_users[key].end(); it++) {
        if(id == it->id) {
            user = &(*it);
            break;
        }
    }
    return user;
}



USER* OPENED_HASH::search_by_name(string name) {

    USER* user = NULL;
    list<USER>::iterator it;
    unsigned int key = this->hash_function_name(name);

    for(it=_users[key].begin(); it!=_users[key].end(); it++) {
        if(name == it->name) {
            user = &(*it);
            break;
        }
    }
    return user;
}


void OPENED_HASH::print_by_id(long double id) {
    USER* user = NULL;
    user = this->search_by_id(id);
    if (user != NULL) {
        cout << user->univ << " " << user->id << " " ;
        cout << user->name << " " << user->tweets << " " ;
        cout << user->friends << " " << user->followers << " " ;
        cout << user->date << endl;
    } else {
        cout << "NONE" << endl;
    }
}


void OPENED_HASH::print_by_name(string name) {
    USER* user = NULL;
    user = this->search_by_name(name);
    if (user != NULL) {
        cout << user->univ << " " << user->id << " " ;
        cout << user->name << " " << user->tweets << " " ;
        cout << user->friends << " " << user->followers << " " ;
        cout << user->date << endl;
    } else {
        cout << "NONE" << endl;
    }
}


void OPENED_HASH::print_table_usage(void) {
    for (int j=0; j<_table_size; j++)
        cout << _users[j].size() << endl;
}


void OPENED_HASH::print_load(void) {
    cout << _load << endl;
}



///////////////////////////////////////
//////////// CLOSED HASH //////////////
///////////////////////////////////////

class CLOSED_HASH {

    private:

        vector<USER> _users;
        int _table_size = 32993;
        int _total_elements = 0;
        float _load;

    public:

        int repeated = 0;
        CLOSED_HASH(void);
        unsigned int hash_function_id(long double);
        unsigned int hash_function_name(string);
        void add_by_id(long double, USER);
        void add_by_name(string, USER);
        USER* search_by_id(long double);
        USER* search_by_name(string);
        void print_by_id(long double);
        void print_by_name(string);
        void print_load(void);

};


CLOSED_HASH::CLOSED_HASH(void){

    USER emptyUser;
    emptyUser.name = string("");
    emptyUser.id = 0;

    for(int i=0; i<_table_size; i++) {
        _users.push_back(emptyUser);
    }
}


unsigned int CLOSED_HASH::hash_function_id(long double id) {

    unsigned int key = 0;
    key = ((unsigned int)id)%_table_size;

    return(key);
}


unsigned int CLOSED_HASH::hash_function_name(string name) {
    unsigned int key = 0;
    for (int i=0; i<name.size(); i++)
        key += (unsigned int)name[i]*i*i*i;
    key = key%_table_size;

    return(key);
}


// add id/user
void CLOSED_HASH::add_by_id(long double id, USER x) {

    if (this->search_by_id(id) != NULL) {

        repeated++;
        return;

    } else {

        if (_total_elements >= _table_size) {
            // sera necesario incrementar el tamaño de la hash table
        }

        // se intenta guardar el usuario desde key hasta final de la hash table
        unsigned int hash = this->hash_function_id(id);
        unsigned int key = hash;
        while (key < _table_size) {

            if(_users[key].id == 0) { // si el slot esta vacio se guarda
                _users[key] = x;
                _total_elements++;
                _load = 1.0*_total_elements/_table_size;
                return;
            }
            key++;
        }

        // se intenta guardar el usuario desde el inicio de la hash table hasta key
        key = 0;
        while (key < hash) {

            if(_users[key].id == 0) { // si el slot esta vacio se guarda
                _users[key] = x;
                _total_elements++;
                _load = 1.0*_total_elements/_table_size;
                return;
            }
            key++;
        }

    }

}


// add name/user
void CLOSED_HASH::add_by_name(string name, USER x) {

    if (this->search_by_name(name) != NULL) {

        repeated++;
        return;

    } else {

        if (_total_elements >= _table_size) {
            // sera necesario incrementar el tamaño de la hash table
        }

        // se intenta guardar el usuario desde key hasta final de la hash table
        unsigned int hash = this->hash_function_name(name);
        unsigned int key = hash;
        while (key < _table_size) {

            if(_users[key].id == 0) { // si el slot esta vacio se guarda
                _users[key] = x;
                _total_elements++;
                _load = 1.0*_total_elements/_table_size;
                return;
            }
            key++;
        }

        // se intenta guardar el usuario desde el inicio de la hash table hasta key
        key = 0;
        while (key < hash) {

            if(_users[key].id == 0) { // si el slot esta vacio se guarda
                _users[key] = x;
                _total_elements++;
                _load = 1.0*_total_elements/_table_size;
                return;
            }
            key++;
        }

    }

}


USER* CLOSED_HASH::search_by_id(long double id) {

    USER* user = NULL;
    unsigned int hash = this->hash_function_id(id);
    unsigned int key = hash;


    // se busca desde key hasta final de la hash table
    while (key < _table_size) {

        if(_users[key].id == id) { // si se encuentra la id
            user = &_users[key];
            return(user);
        } else if (_users[key].id == 0) { // si se encuentra un slot vacio asumimos que nunca se guardo la key
            return(user);
        }
        key++;
    }

    // se busca desde inicio de la hash table hasta key
    key = 0;
    while (key < hash) {

        if(_users[key].id == id) { // si se encuentra la id
            user = &_users[key];
            return(user);
        } else if (_users[key].id == 0) { // si se encuentra un slot vacio asumimos que nunca se guardo la key
            return(user);
        }
        key++;
    }

    return(user);

}



USER* CLOSED_HASH::search_by_name(string name) {

    USER* user = NULL;
    unsigned int hash = this->hash_function_name(name);
    unsigned int key = hash;

    // se busca desde key hasta final de la hash table
    while (key < _table_size) {

        if (_users[key].id == 0) { // si se encuentra un slot vacio asumimos que nunca se guardo la key
            return(user);
        } else if(_users[key].name == name) { // si se encuentra la key
            user = &_users[key];
            return(user);
        }
        key++;
    }

    // se busca desde inicio de la hash table hasta key
    key = 0;
    while (key < hash) {

        if (_users[key].id == 0) { // si se encuentra un slot vacio asumimos que nunca se guardo la key
            return(user);
        } else if(_users[key].name == name) { // si se encuentra la key
            user = &_users[key];
            return(user);
        }
        key++;
    }

    return(user);

}


void CLOSED_HASH::print_by_id(long double id) {
    USER* user = NULL;
    user = this->search_by_id(id);
    if (user != NULL) {
        cout << user->univ << " " << user->id << " " ;
        cout << user->name << " " << user->tweets << " " ;
        cout << user->friends << " " << user->followers << " " ;
        cout << user->date << endl;
    } else {
        cout << "NONE" << endl;
    }
}


void CLOSED_HASH::print_by_name(string name) {
    USER* user = NULL;
    user = this->search_by_name(name);
    if (user != NULL) {
        cout << user->univ << " " << user->id << " " ;
        cout << user->name << " " << user->tweets << " " ;
        cout << user->friends << " " << user->followers << " " ;
        cout << user->date << endl;
    } else {
        cout << "NONE" << endl;
    }
}


void CLOSED_HASH::print_load(void) {
    cout << _load << endl;
}



///////////////////////////////////////
//////////////  MAIN  /////////////////
///////////////////////////////////////

int main(int argc, char** argv) {


    // lectura de datos
    ifstream file;
    file.open("universities_followers.csv");
    cout.precision(15);

    string line;
    string word;

    vector<USER> users;
    vector<USER>::iterator iter;
    USER user;

    getline(file,line);
    while(getline(file,line)){

        stringstream ss(line);

        getline(ss,user.univ,',');
        getline(ss,word,',');
        user.id = stold(word);
        getline(ss,user.name,',');
        getline(ss,word,',');
        user.tweets = stoi(word);
        getline(ss,word,',');
        user.friends = stoi(word);
        getline(ss,word,',');
        user.followers = stoi(word);
        getline(ss,user.date,',');

        users.push_back(user);

    }

    file.close();

    // pruebas

    map<long double, USER> users1_std_ordered;
    unordered_map<long double, USER> users1_std_unordered;

    double accum = 0.0;
    clock_t timer;
    int ctr;

    // se genera un vector con datos de prueba aleatorios
    // considerando que son 19908 usuarios distintos
    int total_searches = 1000000;
    vector<int> rand_index;
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,19907);
    for(int i=0; i<total_searches; i++){
        rand_index.push_back(distribution(generator));
    }

    // BST

    BST test_users1;
    BST test_users2;

    ctr = 0;
    accum = 0.0;
    for (iter = users.begin(); iter != users.end(); iter++) {
        timer = clock();
        test_users1.add_by_id(iter->id , *iter);
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (ctr%100==0)
            cout << "BST ID Insert Time: " << accum << endl;
        ctr++;
    }

    ctr = 0;
    accum = 0.0;
    for (iter = users.begin(); iter != users.end(); iter++) {
        timer = clock();
        test_users2.add_by_name(iter->name , *iter);
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (ctr%100==0)
            cout << "BST NAME Insert Time: " << accum << endl;
        ctr++;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users1.search_by_id( users[rand_index[i]].id );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "BST ID Search Time: " << accum << endl;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users2.search_by_name( users[rand_index[i]].name );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "BST NAME Search Time: " << accum << endl;
    }


    // OPENED HASH

    OPENED_HASH test_users3;
    OPENED_HASH test_users4;

    ctr = 0;
    accum = 0.0;
    for (iter = users.begin(); iter != users.end(); iter++) {
        timer = clock();
        test_users3.add_by_id(iter->id , *iter);
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (ctr%100==0)
            cout << "OPENED_HASH ID Insert Time: " << accum << endl;
        ctr++;
    }

    ctr = 0;
    accum = 0.0;
    for (iter = users.begin(); iter != users.end(); iter++) {
        timer = clock();
        test_users4.add_by_name(iter->name , *iter);
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (ctr%100==0)
            cout << "OPENED_HASH NAME Insert Time: " << accum << endl;
        ctr++;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users3.search_by_id( users[rand_index[i]].id );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "OPENED_HASH ID Search Time: " << accum << endl;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users4.search_by_name( users[rand_index[i]].name );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "OPENED_HASH NAME Search Time: " << accum << endl;
    }


    // CLOSED HASH

    CLOSED_HASH test_users5;
    CLOSED_HASH test_users6;

    ctr = 0;
    accum = 0.0;
    for (iter = users.begin(); iter != users.end(); iter++) {
        timer = clock();
        test_users5.add_by_id(iter->id , *iter);
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (ctr%100==0)
            cout << "CLOSED_HASH ID Insert Time: " << accum << endl;
        ctr++;
    }

    ctr = 0;
    accum = 0.0;
    for (iter = users.begin(); iter != users.end(); iter++) {
        timer = clock();
        test_users6.add_by_name(iter->name , *iter);
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (ctr%100==0)
            cout << "CLOSED_HASH NAME Insert Time: " << accum << endl;
        ctr++;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users5.search_by_id( users[rand_index[i]].id );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "CLOSED_HASH ID Search Time: " << accum << endl;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users6.search_by_name( users[rand_index[i]].name );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "CLOSED_HASH NAME Search Time: " << accum << endl;
    }


    // Impossible Search

    // BST

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users1.search_by_id( 0.050 + users[rand_index[i]].id );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "~ BST ID Search Time: " << accum << endl;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users2.search_by_name( users[rand_index[i]].name + string("_?*"));
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "~ BST NAME Search Time: " << accum << endl;
    }


    // OPENED HASH

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users3.search_by_id( 0.050 +  users[rand_index[i]].id );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "~ OPENED_HASH ID Search Time: " << accum << endl;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users4.search_by_name( users[rand_index[i]].name + string("_?*") );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "~ OPENED_HASH NAME Search Time: " << accum << endl;
    }


    // CLOSED HASH

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users5.search_by_id( 0.050 +  users[rand_index[i]].id );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "~ CLOSED_HASH ID Search Time: " << accum << endl;
    }

    accum = 0.0;
    for(int i=0; i<total_searches; i++){
        timer = clock();
        test_users6.search_by_name( users[rand_index[i]].name + string("_?*") );
        accum += (double)(clock() - timer)/CLOCKS_PER_SEC;
        if (i%1000==0)
            cout << "~ CLOSED_HASH NAME Search Time: " << accum << endl;
    }

    //for(int i=0; i<total_searches; i++){
    //    test_users6.print_by_name( users[rand_index[i]].name );
    //}

    test_users1.clean();
    test_users2.clean();

    return(0);

}



