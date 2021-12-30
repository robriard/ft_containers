#! /bin/bash

function main() {
	clang++ -Wall -Wextra -Werror -o ft_vectors srcs/main.cpp && ./ft_vectors > ft_vectors.txt;
	clang++ -Wall -Wextra -Werror -o std_vectors srcs/main.cpp -D STD && ./std_vectors > std_vectors.txt;
	rm ft_vectors std_vectors;
	diff ft_vectors.txt std_vectors.txt | grep -v "Default" > diff.txt;
	rm  ft_vectors.txt std_vectors.txt;
	cat diff.txt
}

main
