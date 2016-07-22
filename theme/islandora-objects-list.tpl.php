<?php

/**
 * @file
 * Render a bunch of objects in a list or grid view.
 */
?>
<?php if (isset($collection_search)) {
  print render($collection_search);
} ?>   
<?php if ($solr_search) : ?>
  <div><?php print $solr_search; ?></div>
<?php endif; ?>

