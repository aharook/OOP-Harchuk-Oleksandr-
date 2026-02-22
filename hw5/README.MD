# Лекція No19
## Тема: 
    Composite і Decorator: концепції та компроміси.

# Патерн Composite (Компонувальник)

### Суть патерну Composite

    Патерн Composite дозволяє працювати з ієрархічними структурами так, ніби вони є єдиною колекцією об’єктів.
    Для цього вводиться спільний базовий інтерфейс Component, який реалізують:

    - Leaf — окремий елемент (не має вкладених об’єктів);

    = Composite — контейнер, який може містити інші Component (Leaf або Composite).

    Таким чином створюється рекурсивна деревоподібна структура.
    Клієнт викликає метод для кореневого елемента, а той автоматично делегує виконання всім дочірнім елементам.

### Проблема, яку вирішує: 
    Коли потрібно працювати з ієрархічними структурами, де як окремі
    елементи, так і групи елементів повинні мати однаковий інтерфейс.

### Переваги: 
    - Уніфікація: Клієнтський код працює з окремими об’єктами та композиціями однаково. 

    - Гнучкість: Легко додавати нові типи компонентів. 

    - Спрощення клієнтського коду: Клієнту не потрібно розрізняти Leaf та Composite.
### Недоліки: 
    - Може ускладнити обмеження типів компонентів у Composite. 

    - Якщо Component має занадто багато методів, деякі Leaf можуть мати порожні реалізації.


### Приклад 1: Робота з різними типами файлів 
    class component{
    public:
    virtual void nameprint() = 0;

    virtual void Size() = 0;

    virtual void show_struckt() = 0;

    };

    class leaf : public component{

    public:
        std::string name;
        double size;

        leaf(std::string name, double size): name(name), size(size) {}  

        void nameprint() override {
            std::cout << name <<std::endl;
        }

        void Size() override{
            std:: cout << size <<std::endl;
        }

        void show_struckt() override {
            std::cout << name << " (" << size << " KB)" << std::endl;
        }
    };

    class composite : public component{
    private:

    std::vector<component*> components;

    public:

    std::string name;
    double size;

    composite(std::string name): name(name) {}


    void add(component* component){

        components.push_back(component);
    }

    void nameprint() override {
        std::cout << "Folder: " << name << std::endl;
    }

    void Size() override {
        double total = 0;

        for (auto c : components) {
            c->Size();
        }
    }
    void show_struckt() override {
        std::cout << name << std::endl;

        for (auto c : components) {
            c->show_struckt();
        }
    }

    };

### Приклад 2: Gui

    class UIComponent {
    public:
        virtual void draw() = 0;
        virtual ~UIComponent() {}
    };

    class Button : public UIComponent {
    private:
        std::string title;

    public:
        Button(const std::string& title) : title(title) {}

        void draw() override {
            std::cout << "Draw Button: " << title << std::endl;
        }
    };

    class TextField : public UIComponent {
    private:
        std::string placeholder;

    public:
        TextField(const std::string& placeholder) : placeholder(placeholder) {}

        void draw() override {
            std::cout << "Draw TextField: " << placeholder << std::endl;
        }
    };

    class Panel : public UIComponent {
    private:
        std::vector<UIComponent*> children;
        std::string name;

    public:
        Panel(const std::string& name) : name(name) {}

        void add(UIComponent* component) {
            children.push_back(component);
        }

        void draw() override {
            std::cout << "Draw Panel: " << name << std::endl;

            for (auto child : children) {
                child->draw();
            }
        }
    };

# Лекція No20
## Тема: 
    Adapter, Facade, Proxy: інтеграція й спрощення.

