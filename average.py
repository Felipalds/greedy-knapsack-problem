import pandas as pd

pd.options.display.float_format = '{:.8f}'.format

df = pd.read_csv('bin_result.csv')

media_por_arquivo = df.groupby('file_name').agg({
    'time_taken': 'mean',
    'total_profit': 'first',
    'total_weight': 'first'
}).reset_index()

media_por_arquivo['time_taken'] = media_por_arquivo['time_taken'].apply(lambda x: f"{x:.8f}")

media_por_arquivo['file_name'] = media_por_arquivo['file_name'].str.replace("./data/Mochila", "")
media_por_arquivo['file_name'] = media_por_arquivo['file_name'].str.replace(".txt", "")

print(media_por_arquivo)

media_por_arquivo.to_csv('average_bin.csv', index=False)
