<!-- template islandora-objects-search-results.tpl.php -->
<?php

/**
 * @file
 * islandora-objects-list.tpl.php
 *
 * Render a bunch of objects in a list or grid view.
 */
?>
<div class="islandora-objects-list">
<?php if ($solr_search) : ?>
  <div>
    <?php print $solr_search; ?>
  </div>
<?php endif; ?>
</div>
