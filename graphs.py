import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

df1 = pd.read_csv('average_bin.csv')
df2 = pd.read_csv('average_frac.csv')

df1 = df1.sort_values(by=df1.columns[0]).reset_index(drop=True)
df2 = df2.sort_values(by=df2.columns[0]).reset_index(drop=True)

df1.iloc[:, 1] = pd.to_numeric(df1.iloc[:, 1], errors='coerce')
df2.iloc[:, 1] = pd.to_numeric(df2.iloc[:, 1], errors='coerce')

difference = df2.iloc[:, 1] - df1.iloc[:, 1]

y_values_file1 = df1.iloc[:, 1]
y_values_file2 = df2.iloc[:, 1]

rows = len(df1)

percentage_difference = ((df2.iloc[:, 1] - df1.iloc[:, 1]) / df1.iloc[:, 1]) * 100
print(f'Diferenca Bruta:\n{difference}')
print(f'\n\nDiferenca Percentual:\n{percentage_difference}')

x_values = range(len(df1))

plt.figure(figsize=(10, 6))

plt.title('Diferença de tempo entre Mochila Binária e Mochila Fracionária')


plt.plot(x_values, y_values_file1, marker='o', linestyle='-', color='b', label='Binária')
plt.plot(x_values, y_values_file2, marker='o', linestyle='-', color='r', label='Fracionária')


plt.xlabel('Quantidade de itens')
plt.ylabel('Diferença de tempo (em segundos)')

plt.xticks(ticks=x_values, labels=df1.iloc[:, 0].values, rotation=45)

plt.grid(False)
plt.legend()
plt.show()

df_porcentagem = pd.DataFrame()
df_porcentagem['porcentagem'] = ((df2.iloc[:, 1] - df1.iloc[:, 1]) / df1.iloc[:, 1]) * 100

x_assintotica = np.linspace(0.1, 22, 400)  # Evitando dividir por zero
y_assintotica = 20 / x_assintotica  # Função assintótica

plt.plot(df_porcentagem.index, df_porcentagem['porcentagem'], marker='o', linestyle='-', color='g', label='Percentual da diferença de tempo entre as soluções')
plt.plot(x_assintotica, y_assintotica, label=r"$y = \frac{200}{x}$", color='red', linestyle='--', linewidth=2)

# Adicionando títulos e rótulos aos eixos
plt.title('Percentual da diferença de tempo entre as soluções')
plt.xlabel('Quantidade de itens na mochila')
plt.ylabel('Percentual da diferença de tempo')
plt.xticks(ticks=x_values, labels=df1.iloc[:, 0].values, rotation=45)

# Exibindo a legenda
plt.legend()

# Exibindo o gráfico
plt.grid(False)
plt.show()



df = pd.read_csv('single_file.csv')

df['normalized_binary_profit'] = df['binary_profit'] / df['fractional_profit'] * 100

fig, ax = plt.subplots(figsize=(10, 6))

indices = range(len(df))
bar_width = 0.35

ax.bar([i - bar_width / 2 for i in indices], df['normalized_binary_profit'], width=bar_width, color='blue', label='Benefício Binária (como % do Beneficio Fracionária)')
ax.bar([i + bar_width / 2 for i in indices], [100] * len(df), width=bar_width, color='red', label='Benefício Fracionária (100%)')

ax.set_xlabel('Quantidade de itens')
ax.set_ylabel('Qualidade (%)')
ax.set_title('Qualidade Binária vs Qualidade Fracionária (Dimensionado para 100%)')
ax.set_xticks(indices)
ax.set_xticklabels(df['file_name'], rotation=90)
ax.legend()

plt.tight_layout()
plt.show()

