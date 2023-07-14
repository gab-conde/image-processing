build:
	g++ -std=c++11 src/*cpp -o project2.out

run:
	./project2.out output/part1.tga layer1.tga multiply pattern1.tga
	./project2.out output/part2.tga car.tga subtract layer2.tga
	./project2.out output/part3.tga layer1.tga multiply pattern2.tga screen text.tga
	./project2.out output/part4.tga layer2.tga multiply circles.tga subtract pattern2.tga
	./project2.out output/part5.tga layer1.tga overlay pattern1.tga
	./project2.out output/part6.tga car.tga addgreen 200
	./project2.out output/part7.tga car.tga scalered 4 scaleblue 0
	./project2.out output/part8_r.tga car.tga onlyred
	./project2.out output/part8_g.tga car.tga onlygreen
	./project2.out output/part8_b.tga car.tga onlyblue
	./project2.out output/part9.tga layer_red.tga combine layer_green.tga layer_blue.tga
	./project2.out output/part10.tga text2.tga flip
