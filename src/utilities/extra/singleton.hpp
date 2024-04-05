/**
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */

template <typename T>
class Singleton{

    /**
     * The Singleton's constructor should always be private to prevent direct
     * construction calls with the `new` operator.
     */
protected:

    static T* instance;

    Singleton<T>(){}

public:

    /**
     * Singletons should not be cloneable.
     */
    Singleton<T>(Singleton<T> &other) = delete;
    /**
     * Singletons should not be assignable.
     */
    void operator=(const Singleton &) = delete;
    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */

    static T* GetInstance(){
        if(instance == nullptr){
            instance = new T();
        }
        return instance;
    }
};

template <typename T>
T* Singleton<T>::instance = nullptr;