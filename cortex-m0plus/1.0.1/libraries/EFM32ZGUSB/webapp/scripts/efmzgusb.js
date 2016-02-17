$(document).ready(function() {

    var request = $.ajax({
        'url': '/getBoardInfo'
    });
    request.done(function(response) {
        $('#brdname').text(response.BRDNAME);
        $('#blver').text(response.BLVER);
        $('#chipid').text(response.CHIPID);
        $('#cpu').text(response.CPU);
        $('#flash').text(response.FLASHSIZE);
        $('#sram').text(response.SRAMSIZE);
        $('#freq').text(response.CLKFREQ);
    });
    request.fail(function(jqXHR, textStatus) {
        alert('Request failed: ' + textStatus);
    });
    setInterval(function() { 
	var request1 = $.ajax({
	    'url': '/getTempVDD'
	});
	request1.done(function(response) {
	    $('#vdd').text(response.upVDD);
	    $('#tempc').text(response.CPUTEMPC);
	    $('#tempf').text(response.CPUTEMPF);
	});
	request1.fail(function(jqXHR, textStatus) {
	    alert('Request1 failed: ' + textStatus);
	});

	var request2 = $.ajax({
	    'url': '/getLEDstates'
	});
	request2.done(function(response) {
	    $('#redled').text(response.REDLED);
	    $('#greenled').text(response.GREENLED);
	    $('#blueled').text(response.BLUELED);
	});
	request2.fail(function(jqXHR, textStatus) {
	    alert('Request2 failed: ' + textStatus);
	});
    }, 1000);
});


