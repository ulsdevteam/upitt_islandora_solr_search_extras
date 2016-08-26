/**
 * @file
 * Javascript file for islandora solr extras
 */

(function ($) {

   $(document).ready(function() {
     // Simply set all search boxes to empty strings.
/*
     $('#islandora-solr-advanced-terms .form-text').each(function(i, obj) {
       $(this).val('');
     });
*/

/*
     // Remove the supplemental search term blocks and the "remove" button for the first search term.
     $('#edit-terms-0-remove').remove();
     while ($('#islandora-solr-advanced-terms > div').length > 1) {
       $('#islandora-solr-advanced-terms').children("div:last").remove();
     }
     // Now, with the last div remaining, remove the last div in there to get rid of the "AND" / "OR" selector 
     $('#islandora-solr-advanced-terms').children("div").children("div:last").remove();

     // Empty the search box
     $('#edit-terms-0-search').val('');
*/
     // Remove those individual + / - facet links
     $('.islandora-solr-facet li .plusminus').remove();

   });
})(jQuery);

