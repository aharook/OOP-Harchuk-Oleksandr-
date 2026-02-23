# Лекція №19: Composite і Decorator – концепції та компроміси

## Суть патерну Composite
    Патерн Composite дозволяє працювати з ієрархічними структурами так, ніби це єдиний об’єкт або колекція об’єктів. Для цього вводиться загальний інтерфейс Component, який реалізують два типи об’єктів:
    - Leaf (листок) – окремий елемент без вкладених компонентів.
    - Composite (композитний контейнер) – елемент, що може містити інші Component (як листки, так і інші композити).

    Таким чином створюється деревоподібна структура. програма викликає метод на "корені", і він автоматично передає виконання всім своїм нащадкам, забезпечуючи роботу всієї ієрархії
### Проблема, яку вирішує
    Іноді потрібно опрацьовувати ієрархічні дані так, щоб і поодинокі об’єкти, і їхні групи (композиції) можна було використовувати однаково. Composite забезпечує єдиний інтерфейс для роботи з одиночними об’єктами і з їхніми колекціями, вирішуючи проблему складної обробки групових операцій.
### Переваги
    - Уніфікація – клієнтський код може однаково працювати з окремими об’єктами та з їх композиціями, не розрізняючи їхній тип.

    - Гнучкість – просто додавати нові класи компонентів, оскільки всі вони реалізують єдиний інтерфейс Component.

    - Спрощення клієнтського коду – клієнту не потрібно перевіряти чи розрізняти Leaf і Composite. Він взаємодіє лише з інтерфейсом базового компонента.

### Недоліки
    - Обмеження типів – важче накласти жорсткі обмеження на склад підлеглих у Composite (наприклад, заборонити певні комбінації).

    - Порожні реалізації – якщо в інтерфейсі Component визначено багато методів, деякі класи Leaf можуть змушені мати «пусті» (незадіяні) реалізації методів, що можуть         збільшувати кодову базу.
### Приклад 1: Робота з файлами різних типів

    class component {
    public:
        virtual void nameprint() = 0;
        virtual void Size() = 0;
        virtual void show_struckt() = 0;
    };

    class leaf : public component {
    public:
        std::string name;
        double size;
        leaf(std::string name, double size): name(name), size(size) {}

        void nameprint() override {
            std::cout << name << std::endl;
        }
        void Size() override {
            std::cout << size << std::endl;
        }
        void show_struckt() override {
            std::cout << name << " (" << size << " KB)" << std::endl;
        }
    };

    class composite : public component {
    private:
        std::vector<component*> components;
    public:
        std::string name;
        double size;
        composite(std::string name): name(name) {}

        void add(component* component) {
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
### Приклад 2: GUI (графічний інтерфейс)

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
# Лекція №20: Adapter, Facade, Proxy – інтеграція й спрощення

## 1. Патерн Adapter (Адаптер)

### Сценарій 1: Інтеграція сторонньої бібліотеки логування.

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
    private:
        FastLog logger;
    public:
        void Log(const std::string& msg) override {
            logger.WriteFast(msg);
        }
    };
### Сценарій 2: Адаптація старих даних.

    class JsonProvider {
    public:
        virtual std::string GetJsonData() = 0;
    };

    class XmlDatabase {
    public:
        std::string GetXmlData() {
            return "<data>123</data>";
        }
    };

    class DataAdapter : public JsonProvider {
    private:
        XmlDatabase db;
    public:
        std::string GetJsonData() override {
            std::string xml = db.GetXmlData();
            // Конвертація XML у JSON (приклад, хардкод)
            return "{ \"data\": \"123\" }";
        }
    };
## 2. Патерн Facade (Фасад)

    class Light {
    public:
        void Off() {
            std::cout << "Світло вимкнено.\n";
        }
    };

    class TV {
    public:
        void On() {
            std::cout << "ТВ увімкнено.\n";
        }
    };

    class SmartHomeFacade {
    private:
        Light light;
        TV tv;
    public:
        void MovieMode() {
            std::cout << "Підготовка до фільму...\n";
            light.Off();
            tv.On();
        }
    };
### Сценарій 2: Оформлення замовлення в магазині.

    class Inventory {
    public:
        bool Check(int id) {
            return true;
        }
    };
    class Payment {
    public:
        void Pay(int amount) {
            std::cout << "Оплачено.\n";
        }
    };
    // Фасад
    class OrderFacade {
    private:
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
### 3. Патерн Proxy (Заступник)

    class IVideo {
    public:
        virtual void Play() = 0;
    };

    class HeavyVideo : public IVideo {
    public:
        HeavyVideo() {
            std::cout << "Завантаження 10GB відео в пам'ять...\n";
        }
        void Play() override {
            std::cout << "Відтворення відео.\n";
        }
    };

    class VideoProxy : public IVideo {
    private:
        HeavyVideo* video = nullptr;
    public:
        void Play() override {
            if (!video) video = new HeavyVideo();
            video->Play();
        }
    };
### Сценарій 2: Захисний проксі.

    class IDatabase {
    public:
        virtual void DeleteData() = 0;
    };

    class RealDatabase : public IDatabase {
    public:
        void DeleteData() override {
            std::cout << "Дані видалено!\n";
        }
    };

    class DatabaseProxy : public IDatabase {
    private:
        RealDatabase db;
        std::string role;
    public:
        DatabaseProxy(const std::string& userRole) : role(userRole) {}
        void DeleteData() override {
            if (role == "Admin") {
                db.DeleteData();
            } else {
                std::cout << "Помилка: Недостатньо прав!\n";
            }
        }
    };
## Як патерни допомагають
    - Adapter (Адаптер, Інтеграція) – дозволяє використовувати існуючий або сторонній код без змін. Адаптер виступає «перекладачем» між клієнтом і сервісом з іншим інтерфейсом, вирішуючи проблему їх несумісності.

    - Facade (Фасад, Спрощення) – спрощує взаємодію з комплексною підсистемою. Фасад зменшує залежність клієнта від великої кількості класів, об’єднуючи складну функціональність за одним простим інтерфейсом.

    - Proxy (Проксі, Контроль доступу) – дозволяє додавати системну логіку (наприклад, кешування, перевірку доступу, відкладене завантаження) «невидимо» для клієнта. Проксі реалізує той же інтерфейс, що й реальний об’єкт, тому клієнт взаємодіє з ним як з оригіналом.

## Ключова відмінність між патернами
    - Adapter – змінює інтерфейс. Адаптер переводить старий інтерфейс на новий, роблячи їх сумісними.

    - Facade – створює новий інтерфейс (спрощений). Фасад об’єднує складний набір підсистем за одним простим інтерфейсом.

    - Proxy – залишає інтерфейс незмінним. Проксі копіює інтерфейс реального об’єкта повністю, забезпечуючи додатковий контроль над його доступом.