/**
 * @file
 * Javascript file for islandora solr extras
 */

(function ($) {

   $(document).ready(function() {

     // Remove those individual + / - facet links
     $('.islandora-solr-facet li .plusminus').remove();

     $('#islandora-solr-advanced-terms div').find('input:text').each(function() {
       text_val = $(this).val();
       if (text_val.indexOf('nfo\\:fedora/pitt') > 0) {
         $(this).val('');
       }
     });

   });
})(jQuery);

