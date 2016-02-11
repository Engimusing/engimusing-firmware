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
});
