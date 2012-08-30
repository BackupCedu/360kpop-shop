<form action="/Search/Keyword" method="post" id="topSearchForm" name="topSearchForm">
	<input type="text" class="searchinput" id="searchKeyword" name="searchKeyword" />
	<a class="submit" href="javascript:void(0);" id="topSearchCmd" name="topSearchCmd">Tìm kiếm</a>
</form>
<script type="text/javascript">
	$(function () {
		$('#topSearchCmd').click(function () {
			$('#topSearchForm').submit();
		});
	});
</script>