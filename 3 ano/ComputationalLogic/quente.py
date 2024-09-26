from time import sleep as wait

print("Olá!")
wait(1)
bem = input("Tudo bem com o senhor? [s/n]")
if bem == "s" or bem == "S":
    print("Que bom!")
else:
    print("Que pena!")
wait(1)
print("Queria te fazer um pedido...")
wait(1)
res = input("Quer lanchar? [s/n]")
if res == "s" or res == "S":
    print("Bora então")
else:
    print("Tudo bem, fica pra próxima então :(")