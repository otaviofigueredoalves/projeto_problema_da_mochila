# Teste 1: Fluxo Básico e Bloqueio de Capacidade (Obrigatório)
Este teste garante que o programa cadastra os itens, define a capacidade, soma os pesos e bloqueia a entrada de itens quando a mochila enche.
## Cadastrar Itens (Opção 1)
    1 ➔ Água ➔ 3 ➔ 10
    1 ➔ Barraca ➔ 8 ➔ 15
    1 ➔ Lanterna ➔ 2 ➔ 7
    1 ➔ Rádio ➔ 4 ➔ 12
## Definir Capacidade (Opção 4)
    4 ➔ 15
## Adicionar Itens na Mochila (Opção 5)
    5 ➔ 0 (Adiciona a Água - Peso acumulado: 3 kg)
    5 ➔ 1 (Adiciona a Barraca - Peso acumulado: 11 kg)
    5 ➔ 3 (Adiciona o Rádio - Peso acumulado: 15 kg)
    5 ➔ 2 (Tenta adicionar a Lanterna - Deve exibir "Capacidade da mochila excedida!")
## Gerar Relatório (Opção 8)
    8 ➔ Deve exibir Água, Barraca e Rádio. Peso: 15 kg, Valor: 37, Capacidade: 100%.

# Teste 2: Alteração de Catálogo e Remoção da Mochila (Níveis 2 e 3)
Continuando com o programa aberto após o Teste 1, vamos testar as funcionalidades extras de edição e remoção.
## Editar um item do Catálogo (Opção 3)
    3 ➔ 2 (Seleciona a Lanterna)
    Novo nome: Lanterna LED
    Novo peso: 1
    Novo valor: 8
## Remover um item da Mochila (Opção 6)
    6 ➔ 0 (Remove a Água da mochila. Libera 3 kg de espaço).
## Adicionar a Lanterna editada (Opção 5)
    5 ➔ 2 (Agora a Lanterna LED entra, pois pesa 1 kg e você tem 3 kg livres).
## Gerar Relatório (Opção 8)
    8 ➔ Deve exibir Barraca, Rádio e Lanterna LED. Peso: 13 kg, Valor: 35, Capacidade: 86.67%.

# Teste 3: Estratégia Automática (Nível 4)
    Ainda no mesmo terminal, vamos testar o Algoritmo Guloso que prioriza os itens de maior valor de importância.

## Ativar Seleção Automática (Opção 7)
    7 (O sistema esvazia a mochila atual e a preenche automaticamente priorizando o valor).

## Gerar Relatório (Opção 8)
    8 ➔ O sistema deve ter escolhido os itens com maior valor (Barraca [15], Rádio [12], Água [10]) até o limite de 15 kg. O resultado deve ser idêntico ao do final do Teste 1.