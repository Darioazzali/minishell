this_dir="$(dirname $0)"
echo "Copying files to entrega/"
rsync -avz --exclude-from="${this_dir}/exclude.txt" $this_dir ${this_dir}/entrega/
