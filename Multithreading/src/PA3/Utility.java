package PA3;
import java.text.SimpleDateFormat;
import java.time.Duration;
import java.time.Instant;
import java.util.Date;
import java.util.concurrent.TimeUnit;

public class Utility {
    private static final SimpleDateFormat dateFormat = new SimpleDateFormat("HH:mm:ss.SS");
	private static final Instant startInstant = Instant.now();

	/**
 	* Utility function for Timestamp
 	* 
 	*/

	public static String getTimestamp() {//returns the current time
	    return dateFormat.format(new Date()).substring(0, 11);
	}

	public static String getZeroTimestamp() {//how long does it take for a thread to execute		
		Duration duration = Duration.between(startInstant, Instant.now());
		long the_duration = duration.toMillis() / 100;
		long durations = the_duration * 100;
		return millisecondsToTimestamp(durations);
	}

	private static String millisecondsToTimestamp(long millis) {//milliseconds to the format of a timestamp
		
		final long hours = TimeUnit.MILLISECONDS.toHours(millis);

		final long minutes = TimeUnit.MILLISECONDS.toMinutes(millis)
				- TimeUnit.HOURS.toMinutes(TimeUnit.MILLISECONDS.toHours(millis));

		final long seconds = TimeUnit.MILLISECONDS.toSeconds(millis)
				- TimeUnit.MINUTES.toSeconds(TimeUnit.MILLISECONDS.toMinutes(millis));

		final long ms = TimeUnit.MILLISECONDS.toMillis(millis)
				- TimeUnit.SECONDS.toMillis(TimeUnit.MILLISECONDS.toSeconds(millis));

		return String.format("%02d:%02d:%02d.%02d", hours, minutes, seconds, ms);
	}
//	
//    public static void main(String[] args) throws InterruptedException {
//    	System.out.println(Utility.getTimestamp());
//    	System.out.println(Utility.getZeroTimestamp());
//    	System.out.println(Utility.millisecondsToTimestamp(100000));
//    }
}
