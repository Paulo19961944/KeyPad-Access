# KEYPAD ACCESS
Esse é um projeto de uma fechadura eletrônica com Arduino. O que ele faz é justamente capturar um valor que é digitado em uma KeyPad e libera o acesso se o código for correto. Caso o código não for o correto, ele irá exibir acesso negado e de acordo com as regras de segurança dele, na terceira tentativa ele bloqueia o acesso, dependendo de alguém externo, seja um sistema ou alguém especializado para abrir a fechadura eletrônica.<br></br>

# MELHORIAS
Para ter melhorias, poderia implementar um sistema onde uma central apenas tivesse o acesso para liberar o acesso caso ele esteja bloqueado. E com isso, poderiamos usar um Broker MQTT, utilizando o MQTTs para liberar o acesso. Além de um código de redundância que ficasse na AWS, Azure ou em qualquer lugar da Nuvem, onde teriamos o código fonte armazenado com todas as políticas de segurança, facilitando a manutenção e possiveis bugs.<br></br>

# LINK DO PROJETO
[Acesse o Link do Projeto Aqui!!!](https://wokwi.com/projects/406610402513610753)
