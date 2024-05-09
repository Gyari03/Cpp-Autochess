#include "../Memtrace/memtrace.h"


#ifndef NHF_REFORMED_LIST_HPP
#define NHF_REFORMED_LIST_HPP


template <class T>
struct Node{
    T *data;
    Node<T>* previous;
    Node<T>* next;

    Node(T* newData):data(newData),previous(nullptr), next(nullptr){}
    ~Node(){delete data;}
    T* getData(){
        return data;
    }
    T* release(){
        T* ptr = data;
        data = nullptr;
        return ptr;
    }
};

template <class T>
class List {
private:
    Node<T>* head;
    Node<T>* tail;
    unsigned int size;
public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    ~List(){
        for(Node<T>* i=head;i!=nullptr;i=i->next){
            if(i->previous!=nullptr){delete i->previous;}
            if(i==tail){delete i;break;}
        }
    }
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

    void deletefromList(T* todelete){//considering it exists in the list
        if(this->head==nullptr){return;}
        //Új tag hozzáadásánál, ha már létezik ott tag akkor kitöröljük onnan az előzőt
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

    //copy constr. and copy=
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

    int getSize()const{
        return size;
    }

    T* operator[](unsigned int index)const{
        if(index>=size){
            return nullptr;
        }
        Node<T>* temp=head;
        for(unsigned int i=0;i!=index;i++){
            temp=temp->next;
        }
        return temp->getData();
    }

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

    void consumeList(List& consumed){ //List this(consumer) consumes the List consumed
        if(consumed.head==nullptr){return;}
        for(Node<T>* i=consumed.head;i!=nullptr;i=i->next){
            this->addtoList(i->release());
        }
        consumed.clear();
    }

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
