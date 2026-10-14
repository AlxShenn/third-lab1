package main

import "fmt"

type Array struct {
	data     []string
	size     int
	capacity int
}

func MInitArray(arr *Array, capacity int) {
	arr.data = make([]string, capacity)
	arr.size = 0
	arr.capacity = capacity
}

func MResize(arr *Array) {
	newCapacity := 4
	if arr.capacity != 0 {
		newCapacity = arr.capacity * 2
	}
	newData := make([]string, newCapacity)
	for i := 0; i < arr.size; i++ {
		newData[i] = arr.data[i]
	}
	arr.data = newData
	arr.capacity = newCapacity
}

func MAddEnd(arr *Array, text string) {
	if arr.size == arr.capacity {
		MResize(arr)
	}
	arr.data[arr.size] = text
	arr.size++
}

func MAddIndex(arr *Array, text string, index int) {
	if index < 0 || index > arr.size {
		fmt.Println("no")
		return
	}
	if arr.size == arr.capacity {
		MResize(arr)
	}
	for i := arr.size; i > index; i-- {
		arr.data[i] = arr.data[i-1]
	}
	arr.data[index] = text
	arr.size++
}

func MGet(arr *Array, index int) string {
	return arr.data[index]
}

func MDeleteIndex(arr *Array, index int) {
	if index < 0 || index >= arr.size {
		fmt.Println("no")
		return
	}
	for i := index; i < arr.size-1; i++ {
		arr.data[i] = arr.data[i+1]
	}
	arr.size--
}

func MReplace(arr *Array, text string, index int) {
	if index < 0 || index >= arr.size {
		return
	}
	arr.data[index] = text
}

func MLength(arr *Array) int {
	return arr.size
}

func MPrint(arr *Array) {
	for i := 0; i < arr.size; i++ {
		fmt.Print(arr.data[i], " ")
	}
	fmt.Print("\n")
}

func MPrintAddresses(arr *Array) {
	for i := 0; i < arr.size; i++ {
		fmt.Printf("[%d] %s | адрес: %p\n", i, arr.data[i], &arr.data[i])
	}
	fmt.Printf("size = %d capacity = %d\n\n", arr.size, arr.capacity)
}

func MFree(arr *Array) {
	arr.data = nil
	arr.size = 0
	arr.capacity = 0
}
