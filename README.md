# Программа для создания файловых ссылок Windows и загрузки их в буфер обмена Flink  v2.0 от 27.07.2025

Программа для создания файловых ссылок Windows и загрузки их в буфер обмена Flink  v2.0 от 27.07.2025

Проект RUBasic.

Программа создает файловые ссылки для файлов и каталогов и отправляет их в буфер обмена для последующей вставки.

Для работы программе необходимо передать (в параметрах командной строки, например, путём перетаскивания мышью) путь к обрабатываемой папке. В идеале это делается через контекстное меню "Отправить".

Пример ссылки:
file://C:\Users\Alex\Documents\SRV\FLink\Описание_файла.txt

Установка

Для установки программы скопируйте папку с программой в удобное место, например, в папку C:\Program Files\

Для удобного взаимодействия с программой:

Создание ссылки в контекстном меню папок и файлов:
- Создайте ярлык к программе. Переименуйте его как вам удобно, например, просто "FLink" или "Создать ссылку".
- В Меню пуск - Выполнить... - ***"shell:sendto"***. Откроется папка **SendTo**, содержащая несколько ярлыков.
- Переместите созданный ярлык программы в эту папку.

Теперь при открытии контекстного меню папки правой кнопкой мыши выберите Отправить - FLink. Программа создаст файловую ссылку для выбранного файла или папки в буфере обмена Windows. Теперь вы можете вставить эту ссылку куда вам нужно.  
  
Если при запуске программы указать ключ **-v** , то программа будет выводить в консоль информацию о работе.

