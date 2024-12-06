# Итоговый проект по Блоку «Основные конструкции C++»

## Условие задачи

Создайте чат со следующим функционалом:
* консольная программа
* регистрация пользователей - логин, пароль, имя
* вход в чат по логину/паролю
* отправка сообщений конкретному пользователю
* обмен сообщениями между всеми пользователями чата одновременно

**Обязательным условием является использование классов.**

**Дополнительно можно реализовать обработку исключений и использование шаблонов.**

При входе в чат у незнакомца (stranger) есть следующие возможности: нажать 1 для регистрации нового пользователя, нажать 2 для входа под существующим пользователем, нажать 3 для входа в на доску сообщений.

В чате реализована база данных на файлах. Отдельный файл для хранения сообщений `messages.txt` и отдельный файл с данными пользователей `users.txt`.

При регистрации (1) программа проверяет на наличие пользователя в базе данных, а также проверяет на недопустимость использования символа "|", так как он используется в базе данных как разделитель. 

При входе (2) незнакомец вводит имя пользователя и пароль. Если проверка на наличие пользователя и верный пароль прошла успешно, незнакомец становится авторизированным пользователем.

Далее можно зайти в доску сообщений (3). Доска имеет специальные команды, такие как:
* при отправке сообщения `1!` выводится список пользователей чата;
* при отправке сообщения вида `2! userName текст сообщения` происходит отправка сообщения указанному пользователю (userName), при этом если его нет в системе -- отобразиться ошибка;
* при отправке сообщения `0!` происходит выход из доски сообщений.
В доске новые сообщения отмечаются как `NEW` в начале строки, а если сообщение отправлено конкретному пользователю, то появляется сокращение `(DM)` от Direct Message.
