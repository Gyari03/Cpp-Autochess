/**
 * @file List.hpp
 * @brief A generikus listát tartalmazó .hpp
 */

#include "../Memtrace/memtrace.h"
#ifndef NHF_REFORMED_LIST_HPP
#define NHF_REFORMED_LIST_HPP

template <class T>
struct Node{
    T *data;                /**< Adat pointere */
    Node<T>* previous;      /**< Előző Node-ra mutató pointer */
    Node<T>* next;          /**< Következő Node-ra mutató pointer */

    Node(T* newData):data(newData),previous(nullptr),next(nullptr){} /**< Konstruktor*/
    ~Node(){delete data;}   /**< Destruktor, felszabadítja az adatot */
    T* getData(){           /**< Adat lekérése */
        return data;
    }
    T* release(){           /**< Adat kibocsátása(nem felszabadítása) és visszaadása */
        T* ptr = data;
        data = nullptr;
        return ptr;
    }
};

template <class T>
class List {
private:
    Node<T>* head;      /**< lista eleje pointer */
    Node<T>* tail;      /**< lista vége pointer */
    size_t size;        /**< lista mérete */
public:

    /**
     * Konstruktor: inicializálja az alapadatokat.
     */
    List() : head(nullptr), tail(nullptr), size(0) {}

    /**
     * Destruktor: felszabadítja a lista elemeit.
     */
    ~List(){
        for(Node<T>* i=head;i!=nullptr;i=i->next){
            if(i->previous!=nullptr){delete i->previous;}
            if(i==tail){delete i;break;}
        }
    }

    /**
     * Új elem hozzáadása a listához.
     */
    void addtoList(T* newData){
        Node<T>* newNode= new Node<T>(newData);
        if(this->head==nullptr){
            this->head = newNode;
            this->tail = newNode;
            size++;
            return;
        }
        this->tail->next=newNode;
        newNode->previous=this->tail;
        this->tail=newNode;
        size++;
    }

    /**
     * Elem törlése a listából.
     */
    void deletefromList(T* todelete){
        if(this->head==nullptr){return;}
        for(Node<T>* i=head;i!=nullptr;i=i->next){
            if(i->data==todelete){
                if(size==1){
                    head=nullptr;
                    tail=nullptr;
                }
                else if(i==tail){
                    i->previous->next=nullptr;
                    tail=i->previous;

                }
                else if(i==head){
                    i->next->previous=nullptr;
                    head=i->next;
                }
                else{
                    i->previous->next=i->next;
                    i->next->previous=i->previous;
                }
                delete i;
                size--;
                return;
            }
        }
    }

    /**
     * Másoló konstruktor: létrehoz egy új listát a paraméterként kapott listából.
     */
    List(const List& list){
        if(list.head==nullptr){
            this->head=nullptr;
            this->tail=nullptr;
            this->size=0;
            return;
        }
        this->size=0;
        for(Node<T>* i=list.head;i!=nullptr;i=i->next){
            this->addtoList(i->data);
        }
    }

    /**
     * Értékadó operátor: másolja a paraméterként kapott lista elemeit az aktuális listába.
     */
    List& operator=(const List& list){
        if(this != &list) {
            if (this->head != nullptr) {
                for (Node<T> *i = head; i != nullptr; i = i->next) {
                    if (i != head) { delete i->previous; }
                    if (i == tail) {
                        delete i;
                        head = nullptr;
                        tail = nullptr;
                        break;
                    }
                }
            }
            this->size = 0;
            for (Node<T> *i=list.head; i != nullptr; i = i->next) {
                this->addtoList((i->data));
            }
        }
        return *this;
    }

    /**
     * Lista méretének lekérése.
     */
    int getSize()const{
        return size;
    }

    /**
     * Indexelő operátor: visszaadja az adott indexű elemet.
     */
    T* operator[](size_t index)const{
        if(index>=size){
            return nullptr;
        }
        Node<T>* temp=head;
        for(size_t i=0;i!=index;i++){
            temp=temp->next;
        }
        return temp->getData();
    }

    /**
     * Lista elemeinek felszabadítása.
     */
    void clear(){
        if(head==nullptr){return;}
        while(head!=nullptr){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    /**
     * A lista elemeinek átvétele egy másik listából.(Elfogyasztja a másikat)
     */
    void consumeList(List& consumed){ 
        if(consumed.head==nullptr){return;}
        for(Node<T>* i=consumed.head;i!=nullptr;i=i->next){
            this->addtoList(i->release());
        }
        consumed.clear();
    }

    /**
     * Lista maximumának keresése.
     */
    T* Maximum(){
        T* maximum = nullptr;
        if(this->size==0){return maximum;}
        maximum = this->head->getData();
        for(Node<T>* i=head->next;i!=nullptr;i=i->next){
            if( (*(i->getData()))>(*maximum) ){maximum = i->getData();}
        }
        return maximum;
    }
};
#endif //NHF_REFORMED_LIST_HPP
