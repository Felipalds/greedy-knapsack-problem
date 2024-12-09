import pandas as pd

binary_df = pd.read_csv('average_bin.csv')
fractional_df = pd.read_csv('average_frac.csv')

binary_df['time_taken'] = binary_df['time_taken'].apply(lambda x: f"{x:.7f}")
fractional_df['time_taken'] = fractional_df['time_taken'].apply(lambda x: f"{x:.7f}")

binary_df = binary_df[['file_name', 'time_taken', 'total_profit', 'total_weight']]
fractional_df = fractional_df[['file_name', 'time_taken', 'total_profit', 'total_weight']]

# Rename the columns to distinguish between binary and fractional
binary_df.rename(columns={
    'time_taken': 'binary_time', 
    'total_profit': 'binary_profit', 
    'total_weight': 'binary_weight'
}, inplace=True)

fractional_df.rename(columns={
    'time_taken': 'fractional_time', 
    'total_profit': 'fractional_profit', 
    'total_weight': 'fractional_weight'
}, inplace=True)

# Merge the dataframes on the 'file_name' column
combined_df = pd.merge(binary_df, fractional_df, on='file_name', how='outer')

print(combined_df)

combined_df.to_csv('single_file.csv', index=False)
