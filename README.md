# upitt_islandora_solr_search_extras

NOTE:  Due to how URL Alias is used here as well as the bulk-generated URLS for Islandora collection objects, there has been the potential for the underlying handler to be used if the alias is not correct for both the "islandora/search_collection/{PID}" and the "/islandora/object/{PID}".  This causes the page to display with two sidebars, thumbnails, and meta DESC.  In order to get the correct URLs, three steps:

1. run the "Solr search collections mapping" at /admin/islandora/tools/upitt_islandora_solr_search_extras
2. run the bulk update at /admin/config/search/path/update_bulk.  This step will result in unique aliases that all have "-0" added to the end of them (because the previous step creates the initial record with the alias)
3. update the records so that both have the same alias.  `update url_alias set alias = REPLACE(alias, '-0', '') where source like '%pitt:collection.%' and alias like '%-0';`

NOTE:  This module requires a patch to a file in the islandora_solr_search 
module.  The /islandora_solr_search/includes/results.inc needs to be modified 
so that the module_invoke_all call is there.

NOTE:  In order for the search navigation links to appear, several changes need to be made to the site's template and css.  For the template, the additions are simply to put the HTML into page--islandora--object.tpl.php just below the $tags and above the $title render code.

    <?php if ($solr_search_links && (count($solr_search_links)>0)): ?>
    <div class="searchnav">
      <ul class="searchnav-links">
      <?php foreach ($solr_search_links as $solr_search_link) : ?>
        <li><?php print $solr_search_link; ?></li>
      <?php endforeach; ?>
      </ul>
      <br class="clearfloat">
    </div>
    <?php endif; ?>

The CSS additions are:

.searchnav {
        height: 0.8em;
	text-align: center;
}
.searchnav-links {
	list-style: none;
	display: inline-block;
}
.searchnav-links li {
	float: left;
	margin: 0 10px;
}

### TODO:
1. Add lastmod timestamp field to the schema for solr_search_sessions.  Every time records are appended, this timestamp should be refreshed.  There needs to be a CRON or a different scheduled process that clears any records from solr_search_sessions that are older than a specific amount of time (perhaps configurable ~ perhaps hard-coded to something like 30 minutes).
2. Add a page_max_retrieved to the schema for solr_search_sessions and modify the code to look at this value before appending more results to the table.  This will store the actual or calculated page # of search results that is currently stored.  When pulling new solr results, the values between the current page index and the last page_max_retrieved will need to be loaded into the table so that everything stays in order.  This way, there will be no gaps.  If the current page index is 0 and the next click is "last »" which takes the user to page 199 (and there are 20 items per page), the solr query will need to get 3,980 records.
 
