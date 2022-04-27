package PA3;

import java.util.List;

public class Stock {

private List<Datum> data = null;

public List<Datum> getData() {
return data;
}

public void setData(List<Datum> data) {
this.data = data;
}

public Datum getDataByIndex(int num) {
	return data.get(num);
}

}

