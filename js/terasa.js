
$(document).ready(function(){
    getData('terasa');

    setLights();
    setTemperature();
    switchLight();
    switchHeat();
});

function switchHeat(){
    $.get('terasa.php?action=chcemTeplo', function( data ) {
        var test=parseInt(data);
        if(test==1){
            document.getElementById('heat').checked=true;
        }   else{
            document.getElementById('heat').checked=false;
        }
    });

    $('#heat').change(function(){
        var hodnota = $(this).val();
        if(document.getElementById('heat').checked){
            hodnota=1;
        }   else{
            hodnota=0;
        }
        $.get('terasa.php?action=nastavTeplo&hodnota=' + hodnota, function( data ) {
            if (data == 1) {
                alert('Updatnute');
            }
        });
    });
}

function switchLight(){
    $.get('terasa.php?action=chcemLight', function( data ) {
        var test=parseInt(data);
        if(test==1){
            document.getElementById('light').checked=true;
        }   else{
            document.getElementById('light').checked=false;
        }
    });

    $('#light').change(function(){
        var hodnota = $(this).val();
        if(document.getElementById('light').checked){
            hodnota=1;
        }   else{
            hodnota=0;
        }
        $.get('terasa.php?action=nastavLight&hodnota=' + hodnota, function( data ) {
            if (data == 1) {
                alert('Updatnute');
            }
        });
    });
}



//Set jas
function setLights() {
    // nastav hodnotu podla DB
    $.get('terasa.php?action=chcemJas', function( data ) {
        document.getElementById('jas').value=parseInt(data);
        $('.aktualnyJas').text("Nastaveny jas: "+data+"%");
    });

    $('#jas').change(function(){
        var hodnota = $(this).val();
        $.get('terasa.php?action=nastavJas&hodnota=' + hodnota, function( data ) {
            if (data == 1) {
                alert('Updatnute');
            }
        });
    });
}

//Set temperature
function setTemperature(){
    $.get('terasa.php?action=chcemTemp', function( data ){
        document.getElementById('temp').value=parseInt(data);
        $('.aktualnaTeplota').text("Nastavena teplota: "+data+"°C");
    });

    $('#temp').change(function(){
        var hodnota=$(this).val();
        $.get('terasa.php?action=nastavTemp&hodnota=' + hodnota, function( data ){
            if(data==1){
                alert('Updatnute');
            }
        });
    });
}

function getData(file) {
    var url = file + '.php?action=getHistoryData';
    var dataToHandle = [];

    $.get( url, function( data ) {
        parseData( data );
    });
}

function parseData(data) {
    var obj = $.parseJSON(data);

    for(var i = 0; i < 20; i++) {
        var datetime = obj[i].timestamp;
        var temperature = obj[i].temp7;
        var humidity=obj[i].humi7;
        var pohyb=obj[i].pirs7;
        var dazd=obj[i].rain0;
        var sunlight=obj[i].dayl0;
        var test=0;

        if(i == 0) {
            $('.teplotaAktualna').text(temperature+"°C");
            $('.vlhkostAktualna').text(humidity+"%");
            if(pohyb==test){
                $('.pohybAktualny').text("Nie");
            }   else{
                $('.pohybAktualny').text("Áno");
            }

            if(dazd==test){
                $('.dazdAktualny').text("Nie");
            }   else{
                $('.dazdAktualny').text("Áno");
            }

            if(sunlight==test){
                $('.sunAktualny').text("Nie");
            }   else{
                $('.sunAktualny').text("Áno");
            }
        }

        if(pohyb==test){
            pohyb="Nie";
        }   else{
            pohyb="Áno";
        }

        if(dazd==test){
            dazd="Nie";
        }   else{
            dazd="Áno";
        }

        if(sunlight==test){
            sunlight="Nie";
        }   else{
            sunlight="Áno";
        }

        var fDate = moment(datetime).format('DD.MM.YYYY / HH:mm');
        var riadok = '<tr><td>'+ fDate+'</td><td>'+ temperature + "°C" +'</td><td>'+ humidity + "%"+ '</td><td>' + pohyb + 
        '</td><td>' + dazd + '</td><td>'+ sunlight + '</td></tr>';

        $('.terasa').append(riadok);
    }

    $('.tableShowHide').click(function(){
        var isVisible = $('.historyTable').css('display');

        if(isVisible == 'none') {
            $('.historyTable').show(500);
            $('.linkText').text('Schovaj detaily');
        } else {
            $('.historyTable').hide(500);
            $('.linkText').text('Ukáž detaily');
        }
    });

    $('.jasShowHide').click(function(){
        var isVisible = $('.nastavenieJasu').css('display');

        if(isVisible == 'none') {
            $('.nastavenieJasu').show(500);
            $('.linkTextJas').text('Schovaj nastavenie jasu');
        } else {
            $('.nastavenieJasu').hide(500);
            $('.linkTextJas').text('Ukáž nastavenie jasu');
        }
    });

    $('.teplotaShowHide').click(function(){
        var isVisible = $('.nastavenieTeploty').css('display');

        if(isVisible == 'none') {
            $('.nastavenieTeploty').show(500);
            $('.linkTextTeplota').text('Schovaj nastavenie teploty');
        } else {
            $('.nastavenieTeploty').hide(500);
            $('.linkTextTeplota').text('Ukáž nastavenie teploty');
        }
    });
}
