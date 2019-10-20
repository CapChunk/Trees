#ifndef ADRASSIL_H
#define ADRASSIL_H
#include <iostream>
#include <new>
#include <cassert>
//TANKS lawliert 89, our code

#define NUMBER 9  // esto define el largo en la lista "Number"

template <typename T> class Node {  // el tipo Template , deja abierto al uso de cualquier tipo de dato, en este caso crearemos, un nodo
public:

    Node<T> *parent, *left, *right;   // Se define con la palabra reservada Node<Tipo de dato> y definimos, izquierda, derecha y 'padre'
    T data;     // y en la variable data, trabajaremos con la informacion

    Node() : parent(NULL), left(NULL), right(NULL) {
        parent = NULL;
        left = NULL;                // Esta parte nos ayuda a construir un nuevo nodo, vacio en todo sentido
         right = NULL;           // No tiene un nodo padre definido, ni izquierda o derecha
    }

    Node(T data) : data(data),  parent(NULL), left(NULL), right(NULL) { //Aqui se inicializa un nodo con datos dentro de un parentesis, definiendo DATA
                                                                                              //Pero sin definir, su espacio en la estructura xd
    }

    Node(T data, Node<T> *parent, Node<T> *left, Node<T> *right) :
        data(data), parent(parent), left(left), right(right) {
        // Aqui se define el nodo completo con las caracteristicas necesarias
        //Se define la DATA , el padre, izquierda y derecha, se reciben con punteros y son los valoers que arroja el tipo NODE
        // (correspondiendo a *left *right y parent),
    }

    static void walk(const Node<T> *tree);
    static Node<T> *find(Node<T> *tree, T value);
    static Node<T> *minimum(Node<T> *tree);
    static Node<T> *maximum(Node<T> *tree);
    static Node<T> *successor(Node<T> *tree);

    //** Always returns the root of the tree, whether it had to be modified
    // or not**

    // Siempre regresa el (techo) nodo principal del arbol, de cualquier forma puedes modificarlo, o no

    static Node<T> *insertNode(Node<T> *tree, Node<T> *node);  // Funcion para insertar un nodo dandole un nodo que se llamara "tree"
                                                                                                                                        // y otro llamado node
    static Node<T> *deleteNode(Node<T> *tree, Node<T> *node);           /// para eliminar un nodo, se requieren los mismos parametros

private:
    static Node<T> *transplant(Node<T> *tree, Node<T> *u, Node<T> *v);  // en privado se declara el metodo "tramsplant " que recibe tres nodos distintos y
                                                                                                                                                      // describiremos en la propia funcion
};

template<typename T> std::ostream &operator<<(std::ostream &output, Node<T> node); // con el operador de salida, se devolvera el nodo al que se haga referencia con
                                                                                              //Los operadores  <<

int main() {
    Node<int> list[NUMBER] = {
        45, 50, 1, 9, 44, 56, 98, 43, 32   //Aqui se usa aquel 9, es para el tamanio de una lista de "Numeros , nodo"
    };

    // construct a tree

    // Plantando un Pino
                        // raiz
    Node<int> *root = NULL;

    // We will just use the first tree as the root

    // ahora usaremos el primer arbol que pide como parametro
    // ahi pondremos la raiz "root"

    for (int i = 0; i < NUMBER; ++i) {   // Aqui lo que hace es insertar la lista de Nodos, numero, de uno en uno con la sobrecarga que no me sabia
                                  //cambiando esta madre                                                                                                                                // (list +1 ) esta bien perra
                                   //por un .size( ) y se chingo, ya template super shido

        root = Node<int>::insertNode(root, (list + i));

    }

    Node<int>::walk(root);  // Aqui se usa la funcion "walk" (caminar), poniendo como parametro la raiz

    std::cout << *Node<int>::find(root, 43);                                  // Se muestra el valor del nodo, usando find(raiz y valor de busqueda)
    std::cout << "Minimum: " << *Node<int>::minimum(root);                // Aqui se usan la funcion, Maximo y minimo
    std::cout << "Maximum: " << *Node<int>::maximum(root);                      // usando como parametro la raiz

    Node<int> *nine = Node<int>::find(root, 9);           // Se declara un "nodo, numero" llamado nine, de tipo apuntador " *nine " y despues, se le iguala, a buscar
    std::cout << "9: " << *nine;                                               // el nodo que tenga el valor de 9 numerico, y se imprime un 9 y el nodo
    std::cout << "Successor: " << *Node<int>::successor(nine);           // aqui se imprime el sucesor del nodo NINE

    Node<int> *fortyFour = Node<int>::find(root, 44);                // En esta madre se hace con el 44
    std::cout << "44: " << *nine;
    std::cout << "Successor: " << *Node<int>::successor(fortyFour);

    root = Node<int>::deleteNode(root, root);       //Aqui se eliminan los nodos utilizando los parametros "raiz, raiz" tal vez
    Node<int>::walk(root);                                          //para eliminar todo el arbol

    return 0;
}

template <typename T> void Node<T>::walk(const Node<T> *tree) {   // Aqui empieza lo bueno
    if (tree == NULL) return;        // si el arbol ta vacio, no esta creado, regresate alv

    walk(tree -> left);                           // se desplatara, de el nodo dado, hacia la izquierda <--
    std::cout << tree -> data << "\n";  //en esta linea, se imprime la data de el nodo en que se encuentra, "a la izq del nodo referencia"
    walk(tree -> right);                           // se deplaza hacia la derecha de el nodo en que se encuentra ahora," recorriendolo en orden "



}

template <typename T> Node<T> *Node<T>::insertNode(Node<T> *tree, Node<T> *node) {  // La funcion recibe el arbol(la raiz), y el nodo a insertar
    if (!tree) {               // si no es igual a esta madre xd
        tree = node;    //igualamos la raiz al nodo que vamos a insertar, osea que es el primer valor
        node -> parent = NULL; // y pos no tiene padre, como el PRESI...
    } else {
        Node<T> *parent, *search = tree;   // Aqui se crea un apuntador tipo NODO Parent y uno Search, que apunta a la raiz
        bool left = false;  // el booleano, izquierda es falso
        while (search != NULL) {        // mientras, el segundo valor del nodo que tomamos de la raiz, no sea nulo
            parent = search;              // igualamos los valores pedidos a la raiz, ahora el *Apuntador NODO 'PADRE' *  es igual a la raiz
            if (node -> data <= search -> data) {// le sacamos el data a los nodos y comparamos, el valor que nos da el nodo a insertar y la raiz
                // con el valor que sacamos de la raiz alv y si el valor nuevo es menor o igual que el valor de la raiz
                search = search -> left; //moveremos el nodo de "raiz" hacia la izquierda, haciendo que "search siga sin ser nulo y continuando el ciclo"
                left = true; //hacemos que nuestro booleano izquierda sea verdadero
            } else {  // en caso de que no sea menor o igual los datos comparados
                search = search -> right;     // el "El nodo raiz" se movera a la derecha
                left = false;  //y "LEFT" se hara falso
            }
        } //en el momento que  se encuentre posicionado en un nodo padre, apuntando a un nodo vaio
        node -> parent = parent; // el nodo padre se quedara donde esta
        if (left) parent -> left = node; // en caso de que "left "sea verdadero, el nodo se insertara a la izquierda
        else parent -> right = node; // en caso contrario lo hara a la derecha
    }

    return tree; // se devuelve el arbol con los elementos insertados
}

template <typename T> Node<T> *Node<T>::find(Node<T> *tree, T value) {  // aqui se define la funcion buscar, que recibe un nodo(raiz) y un valor a buscar
    if (!tree || tree -> data == value) return tree; //si no hay arbol o el dato raiz es el valor, devuelve el valor del arbol
    if (value < tree -> data) return find(tree -> left, value);// si el valor de la raiz es maior al buscado, usa la funcion find, pero tomando de raiz, el nodo de la izquierda y el mismo valor
    else return find(tree -> right, value);// en caso de que el valor raiz sea menor el buscado, le das hacia la derecha morro
}

template <typename T> Node<T> *Node<T>::minimum(Node<T> *tree) {   // Esta es la funcion minimo
    if (!tree) return NULL;

    while (tree -> left) {
        tree = tree -> left;       //mientras haya valores muevete a la izquierda
    }

    return tree; // PUM EL MINIMO VALOR DE TU LISTA xd
}

template <typename T> Node<T> *Node<T>::maximum(Node<T> *tree) {   // Y pues esto es el de MAXIMO, emm..... no lo gua explicar
    if (!tree) return NULL;

    while (tree -> right) {
        tree = tree -> right;
    }

    return tree;
}

template <typename T> Node<T> *Node<T>::successor(Node<T> *node) {    // Aqui se usa la funcion sucesor, de un nodo dado
    if (!node) return NULL;

    if (node -> right) {          // si hay un nodo a la derecha
        return minimum(node -> right);  // regresa el valor minimo, tomando como referencia el nodo a la derecha del dado en la funcion
    } else {

        // We need to traverse upwards in the tree to find a node where
        // the node is the left child of a parent
        // parent is the successor

        //Necesitaremos recorrer el arvol para encontrar un nodo donde
        // el nodo sea "EL HIJO IZQUIERDO" de un padre, y ese padre
        //es el sucesor
        Node<T> *parent = node -> parent;           // el nuevo nodo padre, sera el padre del nodo que nos dieron, puesto que no hay nodos a la derecha
        while(parent && node != parent -> left) {  // mientras el nodo padre o el nodo dado, sean diferentes a el nodo a la izquierda de el nodo de arriba
            node = parent;              //el nodo del que buscamos sucesor, sera su propio padre
            parent = node -> parent; // y su nodo padre, sera el padre de este otro
        }

        return parent; // entonces devolveremos el nodo, de el que es considerado el sucesor, el nodo que nos dieron
        //se hace una clase de "Busqueda inversa", puesto que se toman los padres para hacer una busqueda hasta que se igualen el padre de ambos nodos
        //que seria, del que partiria la busqueda para encontrar el sucesor dado
    }

}

// make node U's paarent have node v has its child
// Hacemos el nodo U padre, que tiene un nodo hijo "v"
template <typename T> Node<T> *Node<T>::transplant(Node<T> *tree, Node<T> *u, Node<T> *v) { // transplantar el arbol, recibiendo el nodo padre donde se asentara
    if (!u -> parent) tree = v; // si el "PADRE DEL NODO PADRE no existe", "tree" sera igualado al hijo  v                                                       Y el nodo hijo v
    // "En caso de que elimines la raiz, esta tomara el valor del hijo"

    else if (u -> parent -> left == u) {
        u -> left = v; // " En caso de que si exista ese nodo, se preguntara, si el dato menor al padre de U es justo U y en caso de ser asi, el hijo v, sera insertado a la izquierda de U"
        //en caso de que no sea la raiz, si somo el valor menor a nuestro padre, insertaremos v a la izquierda

    } else if (u -> parent -> right == u) {//En caso de que, el valor U sea mayor que su padre, que se encuentra a la deresha
        u -> right = v; //el hijo sera insertado a la derecha de U
        //en caso de que seamos el valor mayor de nuestro padre, insertaremos v a la derecha
    }
    if (v) v -> parent = u -> parent; // ya que v esta asignada, el padre de V, sera considerado el padre de U, que seria simplemente U, puesto que
                                                                    // en la manipulacion superior, solo se entra a los ciclos cuando tomando la izquierda o derecha del padre de U
                                                                          // Se llega a U.
    return tree;
}

template <typename T> Node<T> *Node<T>::deleteNode(Node<T> *tree, Node<T> *node) {  //Eliminar nodo
    if (!node -> left) {              // Si no existe un nodo a la izquierda, del seleccionado
        tree = transplant(tree, node, node -> right); // tomamos el arbol desde la raiz y, los valores para la funcion de transplantar (raiz, nodo a eliminar y el nodo a la derecha)

        // la accion anterior dice que si el nodo a eliminar, no tiene un valor menor a el
        // se eliminara el nodo y el valor del hijo, pasara al valor a eliminar

    } else if (!node -> right) { // en caso de se revise y no exista un nodo a la derecha del seleccionado
        tree = transplant(tree, node, node -> left); // el arbol se transplantara tomando (raiz, el nodo a eliminar y su nodo a la izquierda)
        // aqui se hace el mismo proceso que arriba, solo que al no tener un numero menor
        // se transplanta hacia la izquiera, como un numero menor que el que eliminaremos, y esto hara que el arbol conserve el orden

    } else {  // al existir ya ambos nodos conectados al que queremos eliminar

        // Has two children -- successor must be on the right
        // teniendo dos hijos, el sucesor deberia estar a la derecha

        Node <int> *successor = minimum(node -> right); // se toma el sucesor del nodo de la derecha
        assert(successor -> left == NULL);  //assert compara con cero o con una expresion "is false"
        // en caso de que sea falso, que a la izquierda del sucesor sea nulo
        // "En caso de que se encuentre algun valor a la izquierda del sicesor

        if (successor != node -> right) {  // si el sucesor no es igual al nodo que se encuentra a la derecha del que eliminaremos
            tree = transplant(tree, successor, successor -> right);
            successor -> right = node -> right;              //transplantaremos el arbol tomando al(raiz, sucesor, a la derecha del sucesor)
            // y ahora el sucesor a la derecha, tendra el valor del nodo a eliminar a la derecha
            successor -> right -> parent = successor;  // y aqui el nodo que apuntaria a "El nodo padre del nodo a la derecha, del nodo a la derecha del usado como referencia para eliminar"

            // ese nodo, sera igual a succesor, que es el valor minimo, del nodo a eliminar, a la derecha
        }
// en dado caso que el sucesor, sea igual al nodo que esta a la derecha del que queremos eliminar

        tree = transplant(tree, node, successor);  //transplantaremos el arbol utilizando como referencia, el nodo que queremos eliminar, y el minimo de su nodo a la derecha
        successor -> left = node -> left;  // convertimos el nodo a la izquierda del sucesor, en el nodo a la izquierda del que eliminamos
        successor -> left -> parent = successor; // convertimos, el padre, del nodo a la izquierda del que queremos eliminar, en el nodo sucesor
    }
    return tree; // regresamos el arbolito bien beio
}

template<typename T> std::ostream &operator<<(std::ostream &output, Node<T> node) {
    output << "Value: " << node.data;
    if (node.parent) output << " Parent: " << node.parent -> data;                    // Aqui se imprime, un nodo acomodado como:
    if (node.left) output << " Left: " << node.left -> data;                                        // VALOR: <>
    if (node.right) output << " Right: " << node.right -> data;                             // Parent:
    output << "\n";                                                                                                            // Left:
    return output;                                                                                                             //Right
                      }                                                                                                                          // y el salto de linea
#endif // ADRASSIL_H
