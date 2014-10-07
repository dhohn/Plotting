for img in *.eps; do
    filename=${img%.*}
    convert -density 100 "$filename.eps" "$filename.png"
done
