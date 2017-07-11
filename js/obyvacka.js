
$(document).ready(function(){
    getData('obyvacka');

    setLights();
    setTemperature();
    switchLight();
    switchHeat();
});



function switchHeat(){
    $.get('obyvacka.php?action=chcemTeplo', function( data ) {
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
        $.get('obyvacka.php?action=nastavTeplo&hodnota=' + hodnota, function( data ) {
            if (data == 1) {
                alert('Updatnute');
            }
        });
    });
}

function switchLight(){
    $.get('obyvacka.php?action=chcemLight', function( data ) {
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
        $.get('obyvacka.php?action=nastavLight&hodnota=' + hodnota, function( data ) {
            if (data == 1) {
                alert('Updatnute');
            }
        });
    });
}



//Set jas
function setLights() {
    // nastav hodnotu podla DB
    $.get('obyvacka.php?action=chcemJas', function( data ) {
        document.getElementById('jas').value=parseInt(data);
        $('.aktualnyJas').text("Nastaveny jas: "+data+"%");
    });

    $('#jas').change(function(){
        var hodnota = $(this).val();
        $.get('obyvacka.php?action=nastavJas&hodnota=' + hodnota, function( data ) {
            if (data == 1) {
                alert('Updatnute');
            }
        });
    });
}

//Set temperature
function setTemperature(){
    $.get('obyvacka.php?action=chcemTemp', function( data ){
        document.getElementById('temp').value=parseInt(data);
        $('.aktualnaTeplota').text("Nastavena teplota: "+data+"°C");
    });

    $('#temp').change(function(){
        var hodnota=$(this).val();
        $.get('obyvacka.php?action=nastavTemp&hodnota=' + hodnota, function( data ){
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

function parseData( data ) {
    var obj = $.parseJSON(data);

    for(var i = 0; i < 20; i++) {
        var datetime = obj[i].timestamp;
        var temperature = obj[i].temp1;
        var humidity=obj[i].humi1;
        var pohyb=obj[i].pirs1;
        var test=0;
        if(pohyb==test){
            pohyb="Nie";
        }   else{
            pohyb="Áno";
        }

        var fDate = moment(datetime).format('DD.MM.YYYY / HH:mm');
        var riadok = '<tr><td>'+ fDate+'</td><td>'+ temperature + "°C" +'</td><td>'+ humidity + "%"+ '</td><td>' + pohyb + '</td></tr>';

        $('.obyvacka').append(riadok);

        i=i+5;
    }
    for(var j=0;j<2;j++){
        var time=obj[j].timestamp;
        var move=obj[j].pirs1;
        var teplota = obj[j].temp1;
        var vlhkost=obj[j].humi1;
        var test=0;
        if(j==0){
            if(move==test){
                $('.moveCurrent').text("Nebol zaznamenaný pohyb.");
                document.getElementById('dropdown').style.backgroundColor = '#333';
            }   else{
                $('.moveCurrent').text("V čase "+time+" bol zaznamenaný pohyb!");
                document.getElementById('dropdown').style.backgroundColor = "red";
            }
        }
        if(j == 0) {
            $('.tempAktualna').text(teplota+"°C");
            $('.humiAktualna').text(vlhkost+"%");
            if(move==test){
                $('.pohybAktualny').text("Nie");
            }   else{
                $('.pohybAktualny').text("Áno");
            }
            
        }

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
