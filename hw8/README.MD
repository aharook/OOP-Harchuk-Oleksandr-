# JSON vs XML: практичне порівняння

## Структура класу User

Клас містить п'ять властивостей:

    class User {
    private:
        int id;
        std::string name;
        std::string email;
        int age;
        std::string registrationDate;
    
    public:
        User(int id, const std::string& name, const std::string& email, int age, const std::string& registrationDate)
            : id(id), name(name), email(email), age(age), registrationDate(registrationDate) {}

        int getId() const { return id; }
        std::string getName() const { return name; }
        std::string getEmail() const { return email; }
        int getAge() const { return age; }
        std::string getRegistrationDate() const { return registrationDate; }
    };

## Серіалізація в JSON

Вихідний формат JSON:

    {
        "id": 1,
        "name": "Іван Петренко",
        "email": "ivan.petrenko@example.com",
        "age": 28,
        "registrationDate": "2024-01-15"
    }

Метод toJSON():

    std::string User::toJSON() const {
        std::ostringstream oss;
        oss << "{\n"
            << "    \"id\": " << id << ",\n"
            << "    \"name\": \"" << name << "\",\n"
            << "    \"email\": \"" << email << "\",\n"
            << "    \"age\": " << age << ",\n"
            << "    \"registrationDate\": \"" << registrationDate << "\"\n"
            << "}";
        return oss.str();
    }

## Серіалізація в XML

Вихідний формат XML:

    <user>
        <id>1</id>
        <name>Іван Петренко</name>
        <email>ivan.petrenko@example.com</email>
        <age>28</age>
        <registrationDate>2024-01-15</registrationDate>
    </user>

Метод toXML():

    std::string User::toXML() const {
        std::ostringstream oss;
        oss << "<user>\n"
            << "    <id>" << id << "</id>\n"
            << "    <name>" << name << "</name>\n"
            << "    <email>" << email << "</email>\n"
            << "    <age>" << age << "</age>\n"
            << "    <registrationDate>" << registrationDate << "</registrationDate>\n"
            << "</user>";
        return oss.str();
    }

## Порівняння форматів

Розмір: JSON займає менше місця. XML потребує закриваючих тегів для кожного елемента.

Читаність: JSON лаконічний. XML показує структуру тегами, корисний для ієрархічних даних.

Парсування: JSON простіше парсується. XML потребує спеціалізованих парсерів та більше ресурсів.

Метадані: XML дозволяє атрибути (`<user id="1" status="active">`). JSON місить це в значеннях.

## Реальні сценарії застосування


REST API для мобільних: JSON ідеальний. Менший розмір економить трафік, простота парсування прискорює обробку. Здебільшого REST API використовують JSON.

Конфігураційні файли на підприємстві: XML стандарт. Дозволяє складну ієрархію та валідацію через XSD схеми. Spring Framework, WildFly, .NET використовують XML.

Фінансовий обмін даних: XML переважає. Використовується в ISO, SWIFT для точності та регуляторної відповідності. XML забезпечує строгі схеми для фінансових операцій

JSON природно відображається на структури даних у мовах програмування. Парсування JSON потребує менше обчислювальних ресурсів порівняно з XML, що особливо важливо на клієнтській стороні.

Вбудована підтримка в JavaScript. JSON був розроблений на основі синтаксису JavaScript, тому в браузерах він обробляється як власна структура даних. Це дало JSON величезну перевагу в еру, коли JavaScript став домінуючою мовою веб-розробки.

## Сучасні Переваги JSON для веб-додатків

1. Компактність: менші файли, економія трафіку, швидше завантаження.
2. Простота: природно відображується на структури даних у мовах програмування.
3. Швидкість парсування: менше ресурсів, критично важливо для клієнта.
4. Вбудована підтримка в JavaScript: як власна структура даних у браузерах.
5. Відповідність REST та мікросервісам: мінімалізм, швидка розробкаримку спадщини.

### Розширюваність

XML легко розширюється без порушення сумісності. Нові атрибути та елементи можуть додаватися до існуючої структури без того, щоб старі системи зупинилися.

### Екосистема інструментів

Для роботи з XML розроблено величезну кількість інструментів, валідаторів та трансформацій (XSLT). Це вклад робить XML незамінним для складних операцій з обробки даних.
