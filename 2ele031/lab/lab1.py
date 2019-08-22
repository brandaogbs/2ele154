# To add a new cell, type '#%%'
# To add a new markdown cell, type '#%% [markdown]'
#%% Change working directory from the workspace root to the ipynb file location. Turn this addition off with the DataScience.changeDirOnImportExport setting
# ms-python.python added
import os
try:
	os.chdir(os.path.join(os.getcwd(), '2ele031/lab'))
	print(os.getcwd())
except:
	pass
#%% [markdown]
# # Laboratório 01 -- Introdução a Python3
#%% [markdown]
# -------------------
# 
# ## Interpretador

#%%
print("Hello World!!")

#%% [markdown]
# ### Ordem de execução

#%%
print("   *")
print("  ***")
print(" *****")
print("*******")


#%%
print(" *****")
print("   *")
print("  ***")
print("*******")

#%% [markdown]
# ### Operações numéricas

#%%
# Soma
1300 + 37


#%%
# Multiplicação
17*31


#%%
30 ** 2

#%% [markdown]
# --------------------
# ## Variáveis

#%%
print("Olá, meu nome é Betina")
print("Tenho 27 anos")
print("E mais de 1000000 de reais em patrimônio")


#%%
nome = 'Guilherme'
idade = '24'
patrimonio = '163,50'

print("Olá, meu nome é " + nome)
print("Tenho " + idade + " anos")
print("E mais de " + patrimonio + " de reais em patrimônio" )


#%%
#### Exercício 1: 


#%%



