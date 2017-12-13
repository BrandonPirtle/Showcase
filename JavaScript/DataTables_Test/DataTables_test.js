$(document).ready(function(){
	///// generate random 2d array and column names /////
	var dataset = [];
	var row_count = 1000;
	var col_count = 10;
	for (var i = 0 ; i < row_count; i++) {
	    dataset[i] = [];
	    for (var j = 0; j < col_count; j++) {
	        dataset[i][j] = (Math.random() * 5 | 0) + 6;
	    }
	}
	var str = "<thead><tr>";
	for (var i = 0; i < dataset[0].length; i++) {
		str += "<th>" + i + "</th>";
	}
	str += "</tr></thead><tfoot><tr>";
	for (var i = 0; i < dataset[0].length; i++) {
		str += "<th>" + i + "</th>";
	}
	str += "</tr></tfoot>";
	$("#table_test").append(str);
	/////////////////////////////////////////////////////
	var table = $("#table_test").DataTable({
		dom: 'Blftipr', // Buttons, length, filter, table, info, pagination, processing
		data: dataset,
		select: true,
		colReorder: true,
		responsive: true,
		deferRender: true,
		pageLength: 25,
		lengthMenu: [[10, 25, 50, -1],[10, 25, 50, "All"]],
		buttons: [
			{
				extend: 'collection',
				text: 'Save',
				buttons: [
					'copy',
					'csv',
					'excel',
					'pdf',
					'print'
				]
			},
			{
				extend: 'collection',
				text: 'Select',
				buttons: [
					'selectAll',
					'selectNone',
					'selectCells',
					'selectColumns',
					'selectRows'
				]
			},
			{
				extend: 'collection',
				text: 'Hide Columns',
				buttons: [
					'columnsToggle'
				]
			}
		]
	});
});