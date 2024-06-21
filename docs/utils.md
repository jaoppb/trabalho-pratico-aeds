# Utils

Funções ou métodos com o identificador iniciando com _ não estão disponíveis em outros arquivos.

## bool _isLeapYear(int year)

Retorna `false` para caso o ano passado não seja bissexto e `true` para caso o ano seja bissexto.

## int _getMonthDays(int month, int year)

Recebe um determinado mês e o ano e retorna quantos dias aquele mês tem no ano passado.

## time_t parseDate(std::string date)

Recebe uma string nos seguintes formatos:
 - dd/mm/aaaa - hh:mm:ss
 - dd/mm/aaaa

Retorna o timestamp equivalente a string `date`.

Caso a data seja inválida retorna um `std::runtime_error` com a mensagem "Data inválida".