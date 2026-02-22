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

## 1. Патерн Adapter (Адаптер)
### Сценарій 1: Інтеграція сторонньої бібліотеки логування
    class ILogger {
    public: 
    virtual void Log(const std::string& msg) = 0;
    };

    class FastLog {
    public: 
    void WriteFast(const std::string& text) { 
        std::cout << "FastLog: " << text << "\n"; 
        }
    };

    class FastLogAdapter : public ILogger {
        FastLog logger;
    public:
        void Log(const std::string& msg) override {
             logger.WriteFast(msg); 
             } 
    };

### Сценарій 2: Адаптація старих даних

    class JsonProvider {
    public: 
    virtual std::string GetJsonData() = 0;
    };


    class XmlDatabase {
    public: 
    std::string GetXmlData(){ 
        return "<data>123</data>"; }
    };


    class DataAdapter : public JsonProvider {
        XmlDatabase db;
    public:
        std::string GetJsonData() override {
            std::string xml = db.GetXmlData();
            return "{ \"data\": \"123\" }"; // Конвертація XML у JSON
        }
    };

## 2. Патерн Facade (Фасад)
### Сценарій 1: Керування "Розумним домом"
    class Light { 
    public: 
        void Off() { std::cout << "Світло вимкнено.\n"; } 
    };

    class TV { 
    public: 
    void On() { std::cout << "ТВ увімкнено.\n"; } 

    };

    class SmartHomeFacade {
        Light light;
        TV tv;
    public:
        void MovieMode() {
            std::cout << "Підготовка до фільму...\n";
            light.Off();
            tv.On();
        }
    };
### Сценарій 2: Оформлення замовлення в магазині
    class Inventory { 
        public: bool Check(int id) {
            return true; } 
            };
    class Payment { 
    Public: 
    void Pay(int amount) { 
        std::cout << "Оплачено.\n"; } 
    };

    // Фасад
    class OrderFacade {
        Inventory inventory;
        Payment payment;
    public:
        void Buy(int productId, int price) {
            if (inventory.Check(productId)) {
                payment.Pay(price);
                std::cout << "Замовлення оформлено!\n";
            }
        }
    };
## 3. Патерн Proxy (Заступник)
### Сценарій 1: Віртуальний проксі
    class IVideo { 
        public: virtual void Play() = 0; };

    class HeavyVideo : public IVideo {
    public:
        HeavyVideo() { 
        std::cout << "Завантаження 10GB відео в пам'ять...\n"; }
        void Play() override { 
        std::cout << "Відтворення відео.\n"; }
    };


    class VideoProxy : public IVideo {
        HeavyVideo* video = nullptr;
    public:
        void Play() override {
            if (!video) video = new HeavyVideo(); 
            video->Play();
        }
    };

### Сценарій 2: Захисний проксі

    class IDatabase { 
        public: 
        virtual void DeleteData() = 0; };

    class RealDatabase : public IDatabase {
    public: void DeleteData() override { std::cout << "Дані видалено!\n"; }
    };

    class DatabaseProxy : public IDatabase {
        RealDatabase db;
        std::string role;
    public:
        DatabaseProxy(std::string userRole) : role(userRole) {}
        void DeleteData() override {
            if (role == "Admin") {
                db.DeleteData();
            } else {
                std::cout << "Помилка: Недостатньо прав!\n";
            }
        }
    };

### Як патерни допомагають:

    Adapter (Інтеграція): Дозволяє повторно використовувати існуючий або сторонній код без його модифікації. Він розв'язує проблему несумісності, виступаючи "перекладачем" між клієнтом і сервісом.

    Facade (Спрощення): Зменшує залежність клієнта від десятків класів підсистеми. Клієнтський код стає чистим, а складна логіка інкапсулюється всередині Фасаду.

    Proxy (Контроль доступу): Дозволяє додавати системну логіку (кешування, перевірку прав, ледаче завантаження) непомітно для клієнта, оскільки Проксі маскується під реальний об'єкт.

### Ключова відмінність між патернами:

    Adapter змінює інтерфейс (адаптує старий до нового).

    Facade створює новий інтерфейс (спрощує групу складних інтерфейсів до одного простого).

    Proxy залишає інтерфейс незмінним (повністю копіює інтерфейс оригіналу, щоб контролювати доступ до нього).