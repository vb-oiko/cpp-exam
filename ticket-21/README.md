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

Тип «Робочий графік» визначте як перерахування (enum) із значеннями полів «звичайний», «позмінний», «гнучкий», «на запит».

Тип «Людина» визначте як клас, який містить:
- поля з ім’ям, прізвищем та типу Date з датою народження;
- усі необхідні методи, реалізовані відповідно до загальних вимог.

Тип «Працівник» визначте як клас, похідний від типу «Людина», який містить:
- поле цілого типу як ідентифікатор працівника;
- поле «Робочий графік» та типу Date з датою працевлаштування;
- усі необхідні методи, реалізовані відповідно до загальних вимог.

Тип «Менеджер» визначте як клас, похідний від типу «Працівник», який містить:
- поле з інформацією про працівників, які підпорядковуються цьому менеджеру;
- функцію для додавання нового працівника, підпорядкованого цьому менеджеру;
- функцію для виведення працівника з найбільшим досвідом роботи серед підпорядкованих цьому менеджеру;
- усі інші необхідні методи, реалізовані відповідно до загальних вимог.

## Демонстраційний приклад. 

Створіть об’єкти типу «Менеджер» відповідно до загальних вимог, за потреби — окремі допоміжні об’єкти інших типів. Продемонструйте роботу кожного з методів, описаних у цьому класі.
