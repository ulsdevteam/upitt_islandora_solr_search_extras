<!-- template islandora-solr-wrapper.tpl.php -->
<?php if (isset($messages)) { print $messages; } ?>

  <?php if (isset($tabs)): ?>
  <div class="tabs"><?php print render($tabs); ?></div>
  <?php endif; ?>
  <?php if (isset($action_links)): ?>
  <ul class="action-links">
    <?php print render($action_links); ?>
  </ul>
  <?php endif; ?>

  <?php if (isset($collection_page_metadata) && $is_first_page): ?>
    <div id="metadata-sidebar" style="width: 33%; float: right; margin-left: 20px;">
      <div class="islandora-basic-collection-metadata">
      <?php print $collection_page_metadata; ?> 
      </div>
    </div>
  <?php endif; ?>
    <?php print render($title_prefix); ?>

<div class="islandora-solr-content">
  <div id="islandora-solr-top">
    <?php print $secondary_profiles; ?>
    <div id="islandora-solr-result-count">
      <?php print $islandora_solr_result_count; ?>
    </div>
  </div>
  <?php print $solr_pager; ?>
  <?php print $results; ?>
  <?php print $solr_debug; ?>
  <?php print $solr_pager; ?>
</div>

</div><!-- /end main-content -->

