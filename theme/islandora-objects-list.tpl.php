<?php

/**
 * @file
 * Render a bunch of objects in a list or grid view.
 */
?>
<!-- template islandora-objects-list.tpl.php -->
<?php print $whamjack_sidebar; ?>

<?php if ($solr_search) : ?>
  <div><?php print $solr_search; ?></div>
<?php endif; ?>
