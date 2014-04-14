#Ahora puedo subir los archivos a github mas facilmente B°)
#Pone como mensaje del commit el nombre de la carpeta que contiene a los archivos
#Copiar o crear un enlace simbolico en /bin/ para poder ejecutar en cualquier carpeta
git add $*
message=$(pwd | awk 'BEGIN {FS="/"}; {print $NF}')
git commit -m $message
git push
