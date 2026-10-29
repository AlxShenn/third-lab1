package structures

import "fmt"

type Array struct {
	Data     []string
	Size     int
	Capacity int
}

func MInitArray(arr *Array, capacity int) {
	arr.Data = make([]string, capacity)
	arr.Size = 0
	arr.Capacity = capacity
}

func MResize(arr *Array) {
	newCapacity := 4
	if arr.Capacity != 0 {
		newCapacity = arr.Capacity * 2
	}
	newData := make([]string, newCapacity)
	for i := 0; i < arr.Size; i++ {
		newData[i] = arr.Data[i]
	}
	arr.Data = newData
	arr.Capacity = newCapacity
}

func MAddEnd(arr *Array, text string) {
	if arr.Size == arr.Capacity {
		MResize(arr)
	}
	arr.Data[arr.Size] = text
	arr.Size++
}

func MAddIndex(arr *Array, text string, index int) {
	if index < 0 || index > arr.Size {
		fmt.Println("no")
		return
	}
	if arr.Size == arr.Capacity {
		MResize(arr)
	}
	for i := arr.Size; i > index; i-- {
		arr.Data[i] = arr.Data[i-1]
	}
	arr.Data[index] = text
	arr.Size++
}

func MGet(arr *Array, index int) string {
	return arr.Data[index]
}

func MDeleteIndex(arr *Array, index int) {
	if index < 0 || index >= arr.Size {
		fmt.Println("no")
		return
	}
	for i := index; i < arr.Size-1; i++ {
		arr.Data[i] = arr.Data[i+1]
	}
	arr.Size--
}

func MReplace(arr *Array, text string, index int) {
	if index < 0 || index >= arr.Size {
		return
	}
	arr.Data[index] = text
}

func MLength(arr *Array) int {
	return arr.Size
}

func MPrint(arr *Array) {
	for i := 0; i < arr.Size; i++ {
		fmt.Print(arr.Data[i], " ")
	}
	fmt.Print("\n")
}

func MPrintAddresses(arr *Array) {
	for i := 0; i < arr.Size; i++ {
		fmt.Printf("[%d] %s | адрес: %p\n", i, arr.Data[i], &arr.Data[i])
	}
	fmt.Printf("size = %d capacity = %d\n\n", arr.Size, arr.Capacity)
}

func MFree(arr *Array) {
	arr.Data = nil
	arr.Size = 0
	arr.Capacity = 0
}