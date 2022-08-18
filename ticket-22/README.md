## Загальна специфікація. 

Побудуйте аналітичну діаграму класів, яка характеризує об’єктно-орієнтовану модель запропонованої задачі. Наведіть оголошення класів з описом їхніх полів та методів відповідно до варіанту завдання.

У кожному класі, який визначається, необхідно передбачити:
- конструктори умовчання, з параметрами та копіювання;
- деструктор;
- функції-селектори для доступу окремо до кожного поля;
- функції-модифікатори окремо для кожного з полів;
- функцію для виведення на екран інформації про поточний стан об’єкта.

Реалізації всіх методів припустимо подати у скороченому вигляді без перевірки коректності вхідних параметрів. Значення для аргументів конструктора з параметрами передбачити через введення з клавіатури. Реалізації функцій-селекторів, функцій-модифікаторів та функцій для виведення інформації можна навести тільки для будь-якого одного класу.

Побудуйте демонстраційний тестовий приклад, оформлений у методі main(), у межах якого створіть три об’єкти вказаного типу (для демонстрації виклику кожного конструктора). При виконанні завдання обов’язково дотримуйтесь основних принципів ООП.

Клас Date вважати уже визначеним, оголошення і реалізацію надавати не потрібно!

## Постановка задачі. 

Тип «Відзнака» визначте як перерахування (enum) із значеннями полів «грамота», «диплом», «похвальний лист», «медаль».

Тип «Людина» визначте як клас, який містить:
- поля з ім’ям, прізвищем та типу Date з датою народження;
- усі необхідні методи, реалізовані відповідно до загальних вимог.

Тип «Досягнення» визначте як клас, який містить:
- поля типу «Відзнака» та типу Date з датою вручення відзнаки за досягнення;
- усі необхідні методи, реалізовані відповідно до загальних вимог.

Тип «Переможець» визначте як клас, похідний від типу «Людина», який містить:
- поле з інформацією про усі досягнення переможця;
- функцію для додавання нового досягнення;
- функцію для виведення останнього (за датою) досягнення, яке було відмічене вказаною відзнакою;
- перевантаження оператора порівняння для порівняння двох об’єктів типу «Переможець» за кількістю досягнень;
- усі інші необхідні методи, реалізовані відповідно до загальних вимог.

## Демонстраційний приклад. 

Створіть об’єкти типу «Переможець» відповідно до загальних вимог, за потреби — окремі допоміжні об’єкти інших типів. Продемонструйте роботу кожного з методів, описаних у цьому класі.