package main

import (
    "encoding/json"
    "fmt"
    "log"
    "net/http"
	"strings"
	
	"github.com/PuerkitoBio/goquery"
)

type Song struct {
	Img 	string
	Name 	string
	Artist 	string
	Album 	string
}

func parseMelon() []string {
	// Request the HTML Page.
	res, err := http.Get("https://www.melon.com/chart/index.htm")
	if err != nil {
		log.Fatal(err)
	}

	defer res.Body.Close()
	if res.StatusCode != 200 {
		log.Fatalf("Status Code Error: %d %s", res.StatusCode, res.Status)
	}

	// Load the HTML DOM
	doc, err := goquery.NewDocumentFromReader(res.Body)
	if err != nil {
		log.Fatal(err)
	}

	var data []string
	var img_data []string

	// Find the Song items
	doc.Find("div.ellipsis").Each(func(i int, s *goquery.Selection) {
		// For Each item Found, Get the Band and Title
		some := s.Find("a").Text()
		data = append(data, some)
	})
	data = data[6:]
	if strings.Contains(data[0], "재생") {
		data = data[1:]
	}
	fmt.Println("len:", len(data))

	// Find the Song img items
	doc.Find("img").Each(func(i int, s *goquery.Selection) {
		// For Each item Found, Get the Band and Title
		value, isExist := s.Attr("src")
		if isExist {
			result := strings.Replace(value, "/melon/resize/120/quality/80/optimize", "", 1)
			img_data = append(img_data, result)
		}
	})
	img_data = img_data[26:]
	img_data = img_data[:len(img_data) - 8]
	if strings.Contains(img_data[0], "btn_next.png") {
		img_data = img_data[1:]
	}
	fmt.Println("data: ", img_data)
	fmt.Println("len:", len(img_data))

	for i := 0; i < 100; i++ {
		temp := append([]string{img_data[i]}, data[i + (3 * i):]...)
		data = append(data[:i + (3 * i)], temp...)
	}

	return data
}

func defaultHandler(w http.ResponseWriter, r *http.Request) {
    r.ParseForm()

    fmt.Println("default : ", r.Form)
    fmt.Println("path", r.URL.Path)
    fmt.Println("param : ", r.Form["test_param"])

    for k, v := range r.Form {
        fmt.Println("key : ", k)
        fmt.Println("val : ", strings.Join(v, ""))
    }

	var data = parseMelon()
	songs := []Song{}

	fmt.Println("len:", len(data))

	// Not Clean Artist - Artist * 2
	for i := 0; i < 400; i += 4 {
		sng := Song{Img: data[i], Name: data[i + 1], Artist: data[i + 2], Album: data[i + 3]}
		songs = append(songs, sng)
	}

    doc, _ := json.Marshal(songs)

    fmt.Fprintf(w, string(doc))
}

func main() {
	http.HandleFunc("/api", defaultHandler)
    err := http.ListenAndServe(":3001", nil)
    if err != nil {
        log.Fatal("ListenAndServe : ", err)
    } else {
		fmt.Println("ListenAndServe Started! -> Port(3001)")
    }
}