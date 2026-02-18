# Домашня робота 4

## Тема
    Породжувальні патерни: Factory і Singleton.

### Factory Method 
    Це патерн, який визначає інтерфейс для створення об’єкта, дозволяючи підкласам вирішувати, який саме клас реалізовувати. Основна ідея полягає в тому, що клас-creator не залежить від конкретних реалізацій, а працює через інтерфейс або абстрактний клас.

### Abstract Factory
    Це патерн, який надає інтерфейс для створення цілих сімейств пов’язаних об’єктів. Працює з набором продуктів і використовує композицію.

### Коли доцільно використовувати Factory Method?
    1. Коли потрібно створювати різні реалізації одного інтерфейсу.

    2. Коли клас не знає наперед, який саме об’єкт потрібно створити.

    3. Коли є потреба легко додавати нові типи об’єктів.

Прикладами таких реалізацій є логери: Consoleloger/fileloger

### Коли доцільно використовувати Abstract Factory?

    1. Коли потрібно створювати взаємопов’язані об’єкти.

    2. Коли система має підтримувати різні конфігурації або платформи.

    3. Коли важливо, щоб об’єкти були узгоджені між собою.

Прикладами можуть виступати різні GUI.

### Переваги та недоліки Factory Method

### Переваги:

    Простий у реалізації

    Слабке зв’язування коду

    Відповідає принципу OCP
### Недоліки:

    Збільшує кількість підкласів

    Не підходить для створення сімейств об’єктів

### Переваги та недоліки Abstract Factory

### Переваги:

    Гарантує узгодженість об’єктів

    Легко змінювати цілі сімейства реалізацій

    Підходить для масштабних систем

### Недоліки:

    Складніший у реалізації

    Важко додавати нові типи продуктів

### Висновок

    Factory Method — для простих і гнучких рішень з одним типом об’єктів

    Abstract Factory — для складних систем із взаємопов’язаними об’єктами


# Тема: Поведінкові патерни: Strategy та Observer.

## 1. Патерн Strategy (Стратегія)

### Приклад 1: Вибір способу оплати

    class PaymentStrategy {
    public:
        virtual ~PaymentStrategy() = default;
        virtual void pay(int amount) = 0;
    };

    class CreditCardPayment : public PaymentStrategy {
    public:
        void pay(int amount) override {
            std::cout << "Оплачено " << amount << " грн через Кредитну Карту.\n";
        }
    };

    class PayPalPayment : public PaymentStrategy {
    public:
        void pay(int amount) override {
            std::cout << "Оплачено " << amount << " грн через PayPal.\n";
        }
    };

    class Order {
        std::unique_ptr<PaymentStrategy> strategy;
    public:
        void setPaymentMethod(std::unique_ptr<PaymentStrategy> newStrategy) {
            strategy = std::move(newStrategy);
        }

        void processOrder(int amount) {
            if (strategy) {
                strategy->pay(amount);
            } else {
                std::cout << "Метод оплати не обрано!\n";
            }
        }
    };

### доцільність:

    Ізоляція змін: Якщо банк змінить API для карток, ми правимо тільки клас CreditCardPayment. Клас Order залишається.

    Вибір у Runtime: Користувач обирає метод оплати вже під час роботи програми, і ми просто підставляємо потрібний об'єкт.
### Приклад 2: Поведінка персонажа у грі

    class WeaponStrategy {
    public:
        virtual ~WeaponStrategy() = default;
        virtual void useWeapon() = 0;
    };


    class Sword : public WeaponStrategy {
    public:
        void useWeapon() override { std::cout << "Удар мечем!\n"; }
    };

    class Bow : public WeaponStrategy {
    public:
        void useWeapon() override { std::cout << "Постріл з лука!\n"; }
    };

    class Character {
        std::unique_ptr<WeaponStrategy> weapon;
    public:
        void equipWeapon(std::unique_ptr<WeaponStrategy> newWeapon) {
            weapon = std::move(newWeapon);
        }

        void attack() {
            if (weapon) weapon->useWeapon();
            else std::cout << "Атака кулаками!\n";
        }
    };
   
### Доцільність:

    Уникнення спадкування: Замість створення класів WarriorWithSword, WarriorWithBow, ми реалізовуємо одного Character, який міняє поведінку через композицію. Також можна додати нову зброю, не чіпаючи код персонажа. 

### 2. Патерн Observer (Спостерігач)

### Приклад 1: Погодна станція

class IObserver {
public:
    virtual void update(float temp) = 0;
};

class WeatherStation {
    std::vector<IObserver*> observers;
    float temperature;
public:
    void attach(IObserver* obs) {
        observers.push_back(obs);
    }

    void setTemperature(float temp) {
        temperature = temp;
        notify();
    }

    void notify() {
        for (auto obs : observers) {
            obs->update(temperature);
        }
    }
};

class PhoneDisplay : public IObserver {
public:
    void update(float temp) override {
        std::cout << "Телефон показує: " << temp << "C\n";
    }
};

class Logger : public IObserver {
public:
    void update(float temp) override {
        std::cout << "Запис в лог: Температура змінилась на " << temp << "\n";
    }
};

### Доцільність:

Зв'язок один-до-багатьох: Станція не знає, хто саме її слухає. Ми можемо додати нові типи дисплеїв (наприклад, веб-віджет), не змінюючи код WeatherStation. Також дані оновлюються автоматично на всіх пристроях одразу після зміни температури.

### Приклад 2: Кнопка та Дії

    class Observer {
    public:
        virtual void onEvent() = 0;
    };

    class SoundEffect : public Observer {
    public:
        void onEvent() override { std::cout << "Відтворюю звук 'Клік'!\n"; }
    };

    class Logger : public Observer {
    public:
        void onEvent() override { std::cout << "Записую подію натискання в базу.\n"; }
    };

    class Button {
        std::vector<Observer*> subscribers;
    public:
        void addSubscriber(Observer* s) { subscribers.push_back(s); }
        
        void click() {
            std::cout << "Кнопка натиснута!\n";
            for (auto s : subscribers) s->onEvent(); // Сповіщаємо всіх
        }
    };

### Доцільність:

    Автоматизація: Кнопці не треба знати, які саме класи на неї підписані. Вона просто сповіщає, а підписники реагують. Також можна легко додати або видалити підписника під час роботи програми.
