#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../data_item.h"
#include "../utils.h"

namespace structures
{
    /// <summary> Prvok jednostranne zretazeneho zoznamu. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v prvku. </typepram>
    template<typename T>
    class LinkedListItem : public DataItem<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        /// <param name = "data"> Data, ktore uchovava. </param>
        LinkedListItem(T data);

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> Prvok jednstranne zretazeneho zoznamu, z ktoreho sa prevezmu vlastnosti. </param>
        LinkedListItem(LinkedListItem<T>& other);

        /// <summary> Destruktor. </summary>
        virtual ~LinkedListItem();

        /// <summary> Getter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <returns> Nasledujuci prvok zretazeneho zoznamu. </returns>
        LinkedListItem<T>* getNext();

        /// <summary> Setter nasledujuceho prvku zretazeneho zoznamu. </summary>
        /// <param name = "next"> Novy nasledujuci prvok zretazeneho zoznamu. </param>
        void setNext(LinkedListItem<T>* next);

    protected:
        /// <summary> Nasledujuci prvok zretazeneho zoznamu. </summary>
        LinkedListItem<T>* next_;
    };

    /// <summary> Jednostranne zretazeny zoznam. </summary>
    /// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
    template<typename T>
    class LinkedList : public List<T>
    {
    public:
        /// <summary> Konstruktor. </summary>
        LinkedList();

        /// <summary> Kopirovaci konstruktor. </summary>
        /// <param name = "other"> LinkedList, z ktoreho sa prevezmu vlastnosti. </param>
        LinkedList(LinkedList<T>& other);

        /// <summary> Destruktor. </summary>
        virtual ~LinkedList();

        /// <summary> Vrati pocet prvkov v zozname. </summary>
        /// <returns> Pocet prvkov v zozname. </returns>
        size_t size() override;

        /// <summary> Priradenie struktury. </summary>
        /// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
        /// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
        virtual Structure& assign(Structure& other) override;

        /// <summary> Porovnanie struktur. </summary>
        /// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
        /// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
        virtual bool equals(Structure& other) override;

        /// <summary> Vrati adresou prvok na indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Adresa prvku na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        T& at(int index) override;

        /// <summary> Prida prvok do zoznamu. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        virtual void add(const T& data) override;

        /// <summary> Vlozi prvok do zoznamu na dany index. </summary>
        /// <param name = "data"> Pridavany prvok. </param>
        /// <param name = "index"> Index prvku. </param>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        /// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
        virtual void insert(const T& data, int index) override;

        /// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
        /// <param name = "data"> Odstranovany prvok. </param>
        /// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
        virtual bool tryRemove(const T& data) override;

        /// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
        /// <param name = "index"> Index prvku. </param>
        /// <returns> Odstraneny prvok. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        virtual T removeAt(int index) override;

        /// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
        /// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
        /// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
        virtual int getIndexOf(const T& data) override;

        /// <summary> Vymaze zoznam. </summary>
        virtual void clear() override;

        /// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
        /// <returns> Iterator na zaciatok struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getBeginIterator() override;

        /// <summary> Vrati skutocny iterator na koniec struktury </summary>
        /// <returns> Iterator na koniec struktury. </returns>
        /// <remarks> Zabezpecuje polymorfizmus. </remarks>
        Iterator<T>* getEndIterator() override;

    protected:
        /// <summary> Pocet prvkov v zozname. </summary>
        size_t size_;
        /// <summary> Prvy prvok zoznamu. </summary>
        LinkedListItem<T>* first_;
        /// <summary> Posledny prvok zoznamu. </summary>
        LinkedListItem<T>* last_;

    protected:
        /// <summary> Vrati prvok zoznamu na danom indexe. </summary>
        /// <param name = "index"> Pozadovany index. </param>
        /// <returns> Prvok zoznamu na danom indexe. </returns>
        /// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>
        virtual LinkedListItem<T>* getItemAtIndex(int index);

    private:
        /// <summary> Iterator pre LinkedList. </summary>
        class LinkedListIterator : public Iterator<T>
        {
        public:
            /// <summary> Konstruktor. </summary>
            /// <param name = "position"> Pozicia v zretazenom zozname, na ktorej zacina. </param>
            LinkedListIterator(LinkedListItem<T>* position);

            /// <summary> Destruktor. </summary>
            ~LinkedListIterator();

            /// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> Vrati seba po priradeni. </returns>
            Iterator<T>& operator= (Iterator<T>& other) override;

            /// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
            /// <param name = "other"> Druhy iterator. </param>
            /// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
            bool operator!=(Iterator<T>& other) override;

            /// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
            /// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
            T operator*() override;

            /// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
            /// <returns> Iterator na dalsi prvok v strukture. </returns>
            /// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
            Iterator<T>& operator++() override;

        private:
            /// <summary> Aktualna pozicia v zozname. </summary>
            LinkedListItem<T>* position_;
        };
    };

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(T data) :
        DataItem<T>(data),
        next_(nullptr)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::LinkedListItem(LinkedListItem<T>& other) :
        DataItem<T>(other),
        next_(other.next_)
    {
    }

    template<typename T>
    inline LinkedListItem<T>::~LinkedListItem()
    {
        next_ = nullptr;
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedListItem<T>::getNext()
    {
        return next_;
    }

    template<typename T>
    inline void LinkedListItem<T>::setNext(LinkedListItem<T>* next)
    {
        next_ = next;
    }

    template<typename T>
    inline LinkedList<T>::LinkedList() :
        size_(0),
        first_(nullptr),
        last_(nullptr)
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedList(LinkedList<T>& other) :
        LinkedList<T>()
    {
        assign(other);
    }

    template<typename T>
    inline LinkedList<T>::~LinkedList()
    {
        clear();
    }

    template<typename T>
    inline size_t LinkedList<T>::size()
    {
        return size_;
    }

    template<typename T>
    inline Structure& LinkedList<T>::assign(Structure& other)
    {
        if (this != &other)
        {
            LinkedList<T>& otherLinkedList = dynamic_cast<LinkedList<T>&>(other);

            clear();

            for (T data : otherLinkedList)
            {
                add(data);
            }
        }

        return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::equals(Structure& other)
    {
        if (this == &other)
            return true;

        LinkedList<T>* otherLinkedList = dynamic_cast<LinkedList<T>*>(&other);

        if (otherLinkedList == nullptr || size_ != otherLinkedList->size_)
            return false;

        LinkedListItem<T>* item = first_;
        for (T data : *otherLinkedList)
        {
            if (data != item->accessData())
                return false;

            item = item->getNext();
        }

        return true;
    }

    template<typename T>
    inline T& LinkedList<T>::at(int index)
    {
        //Utils::rangeCheckExcept(index, size_, "LinkedList index out of range (Index: " + std::to_string(index) + ", Size: " + std::to_string(size_) + ")");

        return getItemAtIndex(index)->accessData();
    }

    template<typename T>
    inline void LinkedList<T>::add(const T& data)
    {
        LinkedListItem<T>* item = new LinkedListItem<T>(data);

        if (size_ == 0)
        {
            first_ = item;
        }
        else
        {
            last_->setNext(item);
        }

        last_ = item;
        size_++;
    }

    template<typename T>
    inline void LinkedList<T>::insert(const T& data, int index)
    {
        if (index == size_)
        {
            add(data);
            return;
        }

        LinkedListItem<T>* item = new LinkedListItem<T>(data);

        if (index == 0)
        {
            item->setNext(first_);
            first_ = item;
        }
        else
        {
            //Utils::rangeCheckExcept(index, size_, "LinkedList index out of range (Index: " + std::to_string(index) + ", Size: " + std::to_string(size_) + ")");

            LinkedListItem<T>* previousItem = getItemAtIndex(index - 1);
            item->setNext(previousItem->getNext());
            previousItem->setNext(item);
        }

        size_++;
    }

    template<typename T>
    inline bool LinkedList<T>::tryRemove(const T& data)
    {
        if (size() == 0)
            return false;

        LinkedListItem<T>* item = nullptr;

        if (first_->accessData() == data)
        {
            item = first_;
            first_ = item->getNext();

            if (first_ == nullptr)
            {
                last_ = nullptr;
            }
        }
        else
        {
            LinkedListItem<T>* previousItem = first_;

            while (previousItem->getNext() != nullptr)
            {
                if (previousItem->getNext()->accessData() == data)
                {
                    item = previousItem->getNext();
                    previousItem->setNext(item->getNext());

                    if (item->getNext() == nullptr)
                    {
                        last_ = previousItem;
                    }

                    break;
                }

                previousItem = previousItem->getNext();
            }
        }

        if (item != nullptr)
        {
            size_--;
            delete item;

            return true;
        }

        return false;
    }

    template<typename T>
    inline T LinkedList<T>::removeAt(int index)
    {
        //Utils::rangeCheckExcept(index, size_, "LinkedList index out of range (Index: " + std::to_string(index) + ", Size: " + std::to_string(size_) + ")");

        LinkedListItem<T>* item = nullptr;

        if (index == 0)
        {
            item = first_;
            first_ = item->getNext();

            if (first_ == nullptr)
            {
                last_ = nullptr;
            }
        }
        else
        {
            LinkedListItem<T>* previousItem = getItemAtIndex(index - 1);
            item = previousItem->getNext();
            previousItem->setNext(item->getNext());

            if (item->getNext() == nullptr)
            {
                last_ = previousItem;
            }
        }

        size_--;
        T data = item->accessData();
        delete item;
        return data;
    }

    template<typename T>
    inline int LinkedList<T>::getIndexOf(const T& data)
    {
        LinkedListItem<T>* item = first_;

        for (size_t index = 0; index < size_; index++)
        {
            if (item->accessData() == data)
                return index;

            item = item->getNext();
        }

        return -1;
    }

    template<typename T>
    inline void LinkedList<T>::clear()
    {
        LinkedListItem<T>* item = first_;

        while (item != nullptr)
        {
            first_ = first_->getNext();
            delete item;
            item = first_;
        }

        last_ = nullptr;
        size_ = 0;
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getBeginIterator()
    {
        return new LinkedListIterator(first_);
    }

    template<typename T>
    inline Iterator<T>* LinkedList<T>::getEndIterator()
    {
        return new LinkedListIterator(nullptr);
    }

    template<typename T>
    inline LinkedListItem<T>* LinkedList<T>::getItemAtIndex(int index)
    {
        if (index == size_ - 1)
            return last_;

        LinkedListItem<T>* item = first_;

        for (size_t i = 0; i < index; i++)
        {
            item = item->getNext();
        }

        return item;
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::LinkedListIterator(LinkedListItem<T>* position) :
        position_(position)
    {
    }

    template<typename T>
    inline LinkedList<T>::LinkedListIterator::~LinkedListIterator()
    {
        position_ = nullptr;
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator=(Iterator<T>& other)
    {
        if (this != &other)
        {
            LinkedListIterator& otherLinkedListIterator = dynamic_cast<LinkedListIterator&>(other);

            position_ = otherLinkedListIterator.position_;
        }

        return *this;
    }

    template<typename T>
    inline bool LinkedList<T>::LinkedListIterator::operator!=(Iterator<T>& other)
    {
        LinkedListIterator* otherLinkedListIterator = dynamic_cast<LinkedListIterator*>(&other);

        return otherLinkedListIterator == nullptr ||
            position_ != otherLinkedListIterator->position_;
    }

    template<typename T>
    inline T LinkedList<T>::LinkedListIterator::operator*()
    {
        return position_->accessData();
    }

    template<typename T>
    inline Iterator<T>& LinkedList<T>::LinkedListIterator::operator++()
    {
        position_ = position_->getNext();
        return *this;
    }

}