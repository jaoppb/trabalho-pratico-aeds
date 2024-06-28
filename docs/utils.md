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

## time_t getCurrentTimestamp()

Retorna o timestamp(local: subtrai o fuso-horário) do momento em que a função é chamada.

## void toLower(std::string &str)

Transforma todos os caracteres maiusculos da string `str` passada por referência em caracteres minusculos.

## std::string formatTimestamp(time_t timestamp)

Retorna um string formatada do tipo `dd/mm/aa` com base no `timestamp` passado.